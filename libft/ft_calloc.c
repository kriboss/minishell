/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:59:40 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/20 10:59:42 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	*mem;

	mem = (void *)malloc(num * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, num * size);
	return (mem);
}
