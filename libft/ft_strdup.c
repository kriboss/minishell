/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:23:12 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/21 15:23:21 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(s);
	ptr = (char *)malloc(size + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, size);
	ptr[size] = '\0';
	return (ptr);
}
