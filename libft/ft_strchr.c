/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:35:39 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/19 13:35:40 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while ((char)c != *str)
	{
		if (!*str)
			return (0);
		str++;
	}
	return ((char *)str);
}
/*
#include <stdio.h>

int	main()
{
	char str[] = "tripouille";
	char *res[50];
	*res = ft_strchr(str, 't' + 256);
	printf("character searched: %c\n string: %s", 't' + 256, *res);
	return 0;
}*/
