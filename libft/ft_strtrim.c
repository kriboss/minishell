/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:52:44 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/21 16:52:46 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
/*
#include <stdio.h>

int main()
{
    	char arr[] = "ciao ";
    	char dest[] = "allora mele";
    	char *ptr;

    	// Fill whole array with 0.
    	ptr = ft_strtrim(arr, dest);
    	printf("ptr : %s", ptr);
    	return 0;
}*/
