/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:02:57 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/20 10:02:58 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && i + j < n)
		{
			if (s2[j + 1] == '\0')
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main()
{
    	char arr[] = "ciao allora mela";
    	char dest[] = "allora mela";

    	// Fill whole array with 0.
    	char *res = ft_strnstr(arr, dest, 5);
    	printf("s1 : %s \n s2 : %s \n found : %s", arr, dest, res);
    	return 0;
}*/
