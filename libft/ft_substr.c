/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:36:04 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/21 15:36:06 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	size_t			slen;
	unsigned int	i;

	slen = ft_strlen(s);
	i = 0;
	if (start >= slen)
	{
		subs = ft_calloc(1, sizeof(char));
		if (!subs)
			return (NULL);
		return (subs);
	}
	if (ft_strlen(s) - start < len)
		len = slen - start;
	subs = ft_calloc(sizeof(char), len + 1);
	if (!subs)
		return (NULL);
	while (s[start + i] && i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = "ciao mi chiamo kristian";
	int start = 1;
	int len = 1;
	char	*ptr;
	ptr = ft_substr(s, start, len);
	printf("%s", ptr);
	return 0;
}*/
