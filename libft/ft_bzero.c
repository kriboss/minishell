/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:54:09 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 09:54:12 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *p, size_t n)
{
	ft_memset(p, '\0', n);
	return (p);
}
/*
#include <stdio.h>

int main()
{
    char arr[] = "ciao allora mela";

    // Fill whole array with 0.
    ft_bzero(arr, sizeof(arr));
    printf("After memset:\n");
        printf("%s ", arr);
    

    return 0;
}*/
