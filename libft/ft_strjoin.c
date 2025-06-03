/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:31:16 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/21 16:31:17 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	while (*s1)
		ptr[i++] = *s1++;
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int main()
{
    	char arr[] = "ciao ";
    	char dest[] = "allora mele";
    	char *ptr;

    	// Fill whole array with 0.
    	ptr = ft_strjoin(arr, dest);
    	printf("ptr : %s", ptr);
    	return 0;
}*/
