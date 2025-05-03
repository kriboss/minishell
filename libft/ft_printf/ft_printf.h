/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:36:37 by kbossio           #+#    #+#             */
/*   Updated: 2024/12/01 17:36:38 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);

size_t	ft_putnbr_base(ssize_t nbr, char *base, const char type);
size_t	ft_putstr_fd(const char *s);
size_t	ft_putchar_fd(const char c);
char	*ft_strchr(const char *str, int c);

#endif
