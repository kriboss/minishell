/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:30 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/18 11:58:31 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t		number;

	number = 0;
	while (*str)
	{
		number++;
		str++;
	}
	return (number);
}
/*
#include <stdio.h>

int	main()
{
	char c[] = "ciao cane ciao";
	
	printf("%d", ft_strlen(c));
	return 0;
}
*/
