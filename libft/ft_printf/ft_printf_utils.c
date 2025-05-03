/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:36:14 by kbossio           #+#    #+#             */
/*   Updated: 2025/01/09 17:54:27 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

size_t	print_base(ssize_t nbr, char *base, size_t i)
{
	char	ris[20];
	int		index;

	index = 0;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return (1);
	}
	while (nbr != 0)
	{
		ris[index] = base[nbr % i];
		nbr /= i;
		index++;
	}
	i = index;
	while (--index >= 0)
	{
		write(1, &ris[index], 1);
	}
	return (i);
}

size_t	ft_putnbr_base(ssize_t nbr, char *base, const char type)
{
	size_t	i;
	size_t	cont;

	i = 0;
	cont = 0;
	while (base[i] != '\0')
		i++;
	if (nbr < 0 && (type == 'd' || type == 'i' || type == 'u'))
	{
		cont += ft_putchar_fd('-');
		nbr = -nbr;
	}
	else if (type == 'p' && nbr == 0)
	{
		cont += ft_putstr_fd("(nil)");
		return (cont);
	}
	else if (type == 'p')
		cont += ft_putstr_fd("0x");
	return (cont + print_base(nbr, base, i));
}

size_t	ft_putstr_fd(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr_fd("(null)"));
	while (s[i])
	{
		ft_putchar_fd(s[i]);
		i++;
	}
	return (i);
}

size_t	ft_putchar_fd(const char c)
{
	write(1, &c, 1);
	return (1);
}

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
