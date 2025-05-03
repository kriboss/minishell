/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:13:07 by kbossio           #+#    #+#             */
/*   Updated: 2025/01/09 17:54:23 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

size_t	conv(const char type, va_list args)
{
	char	*lhex;
	char	*uhex;
	size_t	cont;

	lhex = "0123456789abcdef";
	uhex = "0123456789ABCDEF";
	cont = 0;
	if (type == 'c')
		cont += ft_putchar_fd(va_arg(args, int));
	else if (type == 's')
		cont += ft_putstr_fd(va_arg(args, char *));
	else if (type == 'p')
		cont += ft_putnbr_base(va_arg(args, long), lhex, type);
	else if (type == 'd' || type == 'i')
		cont += ft_putnbr_base(va_arg(args, int), "0123456789", type);
	else if (type == 'u')
		cont += ft_putnbr_base(va_arg(args, unsigned), "0123456789", type);
	else if (type == 'x')
		cont += ft_putnbr_base(va_arg(args, unsigned), lhex, type);
	else if (type == 'X')
		cont += ft_putnbr_base(va_arg(args, unsigned), uhex, type);
	else if (type == '%')
		cont += ft_putchar_fd('%');
	return (cont);
}

int	ft_printf(const char *format, ...)
{
	char	*type;
	int		i;
	int		cont;
	va_list	args;

	va_start(args, format);
	type = "cspdiuxX%";
	i = 0;
	cont = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr(type, format[i + 1]))
		{
			cont += conv(format[i + 1], args);
			i++;
		}
		else
			cont += ft_putchar_fd(format[i]);
		i++;
	}
	va_end(args);
	return (cont);
}
/*
#include <stdio.h>

int main() {
    // Test %c with a character
    char c = 'A';
    printf("original: %c\n", c);
    ft_printf("ft_printf character: %c\n", c);


    // Test %d with an integer
    int num = 12345;
    printf("original: %d\n", num);
    ft_printf("ft_printf digit: %d\n", num);

    // Test %i with an integer (should be the same as %d)
    int num2 = -5678;
    printf("original: %i\n", num2);
    ft_printf("ft_printf integer: %i\n", num2);

    // Test %u with an unsigned integer
    unsigned int u_num = 4294967295;
    printf("original: %u\n", u_num);
    ft_printf("ft_printf unsigned integer: %u\n", u_num);

    // Test %x with a hexadecimal number
    int hex_num = 255;
    printf("original: %x\n", hex_num);
    ft_printf("ft_printf lower hexadecimal: %x\n", hex_num);

    // Test %X with a hexadecimal number (uppercase)
    printf("original: %X\n", hex_num);
    ft_printf("ft_printf upper hexadecimal: %X\n", hex_num);

    // Test %p with a pointer (memory address)

    // Test %% to print a literal %
    printf("original: %%\n");
    ft_printf("ft_printf character: %%\n");
    
    printf("printf test%d", printf("ft_printf character: %c\n", c));
    printf("%d", ft_printf("ft_printf character: %c\n", c));
    // Test %s with a string
    char *str = "Hello, ft_printf!";
    printf("original %s \n", str);
    ft_printf("ft_printf string: %s \n", str);
    
    int *ptr = &num;
    printf("original: %p\n", ptr);
    ft_printf("ft_printf pointer: %p\n", ptr);
    return 0;
}*/
