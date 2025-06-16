/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:46 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/16 08:07:48 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int validate_input(char *input)
{
    if (!input || !input[0] || input[0] == '<' || input[0] == '>')
        return (1);
    while (*input == ' ')
        input++;
    if (validate_quote(input) == 1)
        return (1);
    if (validate_pipe(input) == 1)
        return (1);
    if (validate_redirection(input) == 1)
        return (1);
    return (0);
}

int	validate_redirection(char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input  == '"')
		{
			input++;
			while (*input && *input != '\'' && *input != '"')
				input++;
			if (*input)
				input++;
		}
		else if (*input == '<' || *input == '>')
		{
			if (mult_redir(input))
                return (1);
            while (*input == '<' || *input == '>')
				input++;
            while (*input == ' ')
                input++;
			if (!*input || *input == '<' || *input == '>')
				return 1;
		}
		input++;
	}
	return 0;
}

int	mult_redir(char *input)
{
	int c;
    char a;
    
	c = 1;
	a = *input;
	if (*(input + 1) != a && (*(input + 1) == '<' || *(input + 1) == '>'))
		return 1;
    while (*(input + c) == a)
		c++;
    if (c > 2)
    {
        return (1);
    }
	return (0);
}

int	validate_quote(char *str)
{
    int i = 0;
    int d = 0;//outside it
    int s = 0;

    while (str[i])
    {
        if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'))
            i++;
        else
        {
            if (str[i] == '\'' && d == 0)//
                s = !s;//alterna s tra 1 e 0, on and off, in and out
            else if (str[i] == '"' && s == 0)
                d = !d;
        }
        i++;
    }
    if (s == 1 || d == 1)
        return (1);//unclosed quotes
    return (0);//success
}

int validate_pipe(char *input)
{
    int s = 0;
    int d = 0;

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
                return 1;
        }
        else
            input++;
    }
    return 0;
}
