/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:46 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 12:04:29 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_input(char *input)
{
	if (!input || !*input)
		return (0);
	while (*input == ' ')
		input++;
	if (*input == '\0')
		return (0);
	if (validate_quote(input) == 1 || validate_pipe(input) == 1
		|| validate_redirection(input) == 1)
		return (1);
	return (0);
}

int	handle_redirection(char **input)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		if (validate_heredoc(input))
			return (1);
	}
	else if (mult_redir(*input))
		return (1);
	while (**input == '<' || **input == '>')
		(*input)++;
	while (**input == ' ')
		(*input)++;
	if (!**input || **input == '<' || **input == '>')
		return (1);
	return (0);
}

int	validate_redirection(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input;
			input++;
			while (*input && *input != quote)
				input++;
			if (*input == quote)
				input++;
		}
		else if (*input == '<' || *input == '>')
		{
			if (handle_redirection(&input))
				return (1);
		}
		else
			input++;
	}
	return (0);
}

int	validate_quote(char *str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d == 0)
			s = !s;
		else if (str[i] == '"' && s == 0)
			d = !d;
		i++;
	}
	if (s == 1 || d == 1)
		return (1);
	return (0);
}

int	validate_pipe(char *input)
{
	int	s;
	int	d;

	s = 0;
	d = 0;
	if (*input == '|')
		return (1);
	while (*input)
	{
		if (*input == '\'' && d == 0)
			s = !s;
		else if (*input == '"' && s == 0)
			d = !d;
		if (*input == '|' && s == 0 && d == 0)
		{
			input++;
			while (*input == ' ')
				input++;
			if (*input == '\0' || *input == '|')
				return (1);
		}
		else
			input++;
	}
	return (0);
}
