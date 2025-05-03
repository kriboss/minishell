/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:04:01 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 10:04:04 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int main()
{
	char arr[] = "test basic du memcpy !";
	char dest[22];

	// Fill whole array with 0.
	char *r1 = ft_memcpy(dest, arr, 22);
	printf("After memset:");
	printf("%s ", dest);
	printf("%s ", r1);


	return 0;
}*/
