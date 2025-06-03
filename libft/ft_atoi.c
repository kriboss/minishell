/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:30:23 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/20 10:30:25 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				num;
	int				segno;
	int				cont;

	num = 0;
	segno = 1;
	i = 0;
	cont = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (++cont > 1)
			return (0);
		if (str[i] == '-')
			segno = -segno;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * segno);
}
/*
#include <stdio.h>

int main()
{
    // Esempi di test per ft_atoi
    char str1[] = "  12345";
    char str2[] = "  +9876";
    char str3[] = " -42"; // Con spazi iniziali
    char str4[] = " +8 -9999"; // Con segno '+'
    char str5[] = "  -2147483648"; // Con caratteri non numerici

    // Test della funzione ft_atoi
    int ris = ft_atoi(str1);
    printf("ft_atoi(\"%s\") = %d\n", str1, ris); // 12345
    ris = ft_atoi(str2); 
    printf("ft_atoi(\"%s\") = %d\n", str2, ris);  // -9876
    ris = ft_atoi(str3);
    printf("ft_atoi(\"%s\") = %d\n", str3, ris);  // 42
    ris = ft_atoi(str4);
    printf("ft_atoi(\"%s\") = %d\n", str4, ris);  // 9999
    ris = ft_atoi(str5);
    printf("ft_atoi(\"%s\") = %d\n", str5, ris);  // -123

    return 0;
}*/
