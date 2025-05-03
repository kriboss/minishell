/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:55:48 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 13:55:49 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
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
    	char arr[] = "test";
    	char dest[] = "ciao allora mela";

    	// Fill whole array with 0.
    	int i = ft_strncmp(arr, "", 1);
    	printf("difference : %d \n s1 : %s \n s2 : %s", i, arr, dest);
    	return 0;
}*/
