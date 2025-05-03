/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:18:24 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 10:18:25 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*desti;
	const unsigned char	*srci;

	desti = (unsigned char *)dest;
	srci = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (desti < srci)
	{
		while (n--)
			*desti++ = *srci++;
	}
	else
	{
		desti += n - 1;
		srci += n - 1;
		while (n--)
			*desti-- = *srci--;
	}
	return (dest);
}
/*
#include <stdio.h>

int main()
{
    	char dest[50];

    	// Fill whole array with 0.
    	ft_memmove(dest, "ciao", 4);
    	printf("After memset:\n");
	printf("%s", dest);
    

    	return 0;
}*/
