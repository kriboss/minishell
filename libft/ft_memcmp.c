/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:57:44 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/20 09:57:46 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const char	*s1;
	const char	*s2;
	size_t		i;

	s1 = (const char *)str1;
	s2 = (const char *)str2;
	i = 0;
	while (i < n && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char )s2[i]);
}
/*
#include <stdio.h>

int main()
{
    	char arr[] = "cia allora mela";
    	char dest[] = "ciao allora mela";

    	// Fill whole array with 0.
    	int i = ft_memcmp(arr, dest, 0);
    	printf("difference : %d \n s1 : %s \n s2 : %s", i, arr, dest);
    	return 0;
}*/
