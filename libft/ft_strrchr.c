/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:51:48 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 13:51:49 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen((char *)str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	int c = 122;
	char str[] = "ciao io mi chziamo kristian";
	char *res[50];
	*res = ft_strrchr(str, c);
	printf("%s", *res);
	return 0;
}*/
