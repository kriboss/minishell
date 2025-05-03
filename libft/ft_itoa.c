/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:47:12 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/22 10:47:14 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	num;
	size_t			g;

	g = count_digits(n);
	num = n;
	result = (char *)malloc(sizeof(char) * (g + 1));
	if (!result)
		return (NULL);
	result[g--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
	}
	if (n == 0)
		result[0] = '0';
	while (num > 0)
	{
		result[g--] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
/*
#include <stdio.h>

int main() {
    int test_numbers[] = {0, 42, -42, 123456789, -2147483648, 2147483647};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = ft_itoa(test_numbers[i]);
        if (result) {
            printf("ft_itoa(%d) = %s\n", test_numbers[i], result);
            free(result); // Free allocated memory
        } else {
            printf("ft_itoa(%d) failed!\n", test_numbers[i]);
        }
    }

    return 0;
}*/
