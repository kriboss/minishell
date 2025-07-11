/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:43:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 22:38:39 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	add_token(t_shell *shell, char *value, int type, char quote_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->quote = quote_type;
	new_token->type = type;
	new_token->next = NULL;
	if (!shell->tokens)
	{
		shell->tokens = new_token;
		return ;
	}
	else
		tokenadd_back(&shell->tokens, new_token);
}

void	create_token(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '|' )
	{
		add_token(shell, "|", PIPE, 0);
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		add_token(shell, ">>", REDIRECT, 0);
		(*i) += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(shell, ">", REDIRECT, 0);
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(shell, "<<", HEREDOC, 0);
		(*i) += 2;
	}
	else if (input[*i] == '<')
	{
		add_token(shell, "<", REDIRECT, 0);
		(*i)++;
	}
}

static void	handle_variable(t_shell *shell, char *input, int *i)
{
	char	*var_token;
	int		start;

	start = *i;
	(*i)++;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (start + 1 == *i)
	{
		add_token(shell, "$", WORD, 0);
		return ;
	}
	var_token = ft_substr(input, start, *i - start);
	add_token(shell, var_token, WORD, 0);
	free(var_token);
}

void	handle_special(t_shell *shell, char *input, int *i)
{
	char	*quoted_str;
	char	quote;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		quoted_str = extract_quoted(input, i);
		if (!quoted_str)
			return ;
		add_token(shell, quoted_str, WORD, quote);
		free(quoted_str);
	}
	else if (input[*i] == '$')
		handle_variable(shell, input, i);
	else
		create_token(shell, input, i);
}
