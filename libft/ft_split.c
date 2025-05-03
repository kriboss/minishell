/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:55:00 by kbossio           #+#    #+#             */
/*   Updated: 2025/01/19 17:10:15 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(const char *s, char c)
{
	size_t	n;
	int		in;

	n = 0;
	in = 0;
	while (*s)
	{
		if (*s != c && in == 0)
		{
			in = 1;
			n++;
		}
		else if (*s == c)
			in = 0;
		s++;
	}
	return (n);
}

static char	*duping(const char *s, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[len] && c != s[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_all(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**salva;

	i = 0;
	salva = (char **)malloc(sizeof(char *) * (words(s, c) + 1));
	if (!salva || !s)
		return (NULL);
	while (*s)
	{
		while (*s && c == *s)
			s++;
		if (*s)
		{
			salva[i] = duping(s, c);
			if (!salva[i])
				return (free_all(salva, i - 1), NULL);
			i++;
			while (*s && c != *s)
				s++;
		}
	}
	salva[i] = NULL;
	return (salva);
}
/*
#include <stdio.h>

int main()
{
    char str[] = "   ciao  mi chi   kri";
    char delimiter = ' ';
    char **result = ft_split(str, delimiter);
    int i = 0;

    if (!result)
        return (1);

    while (result[i])
    {
        printf("Substring %d: %s\n", i, result[i]);
        i++;
    }
    return (0);
}
*/
