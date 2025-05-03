/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:19:06 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/18 12:19:07 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)p;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>

int main()
{
    char arr[] = "ciao";
    ft_memset(arr, '.', sizeof(arr)-1);
    printf("After memset:\n");
    printf("%s", arr);
    return 0;
}*/
