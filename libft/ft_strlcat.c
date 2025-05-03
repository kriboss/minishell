/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:03:26 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 12:03:27 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0' && i < n)
		i++;
	while (src[j] && i + j + 1 < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < n)
		dest[i + j] = '\0';
	return (i + ft_strlen((char *)src));
}
/*
#include <stdio.h>

int main()
{
    	
    	char dest[50] = "ciao io";
    	const char src[] = "sono lollo";

    	// Fill whole array with 0.
    	int i = ft_strlcat(dest, src, 0);
    	printf("length : %d \n dest : %s", i, dest);
    	return 0;
}*/
