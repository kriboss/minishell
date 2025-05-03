/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:43:57 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 11:43:58 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && i + 1 < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
		dest[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int main()
{
    	char arr[] = "ciao allora mela";
    	char dest[50];

    	// Fill whole array with 0.
    	int i = ft_strlcpy(dest, arr, 20);
    	printf("length : %d \n dest : %s", i, dest);
    	return 0;
}*/
