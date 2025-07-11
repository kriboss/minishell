/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_special.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:36:44 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 23:49:08 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special_special(char c)
{
	if (is_special(c) || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_word(char c)
{
	int	result;

	result = !(is_space(c) || is_special(c));
	return (result);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\b' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
