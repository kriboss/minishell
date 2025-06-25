/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/25 10:17:49 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize(t_shell *shell)
{
	int		i;
	char	*input;
	int		start;

	i = 0;
	input = shell->input;
	while (input[i] && is_space(input[i]))
		i++;
	while(input[i])
	{
		if (is_special(input[i]))
			handle_special(shell, input, &i);
		else if (is_word(input[i]))
		{
			start = i;
			while (input[i] && is_word(input[i]))
				i++;
			char *word = ft_substr(input, start, i - start);
			add_token(shell, word, WORD);
			free(word);
		}
		while (input[i] && is_space(input[i]))
			i++;
	}
}

void	add_token(t_shell *shell, char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
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

void	tok_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*tmp;
	t_token	*prev;

	tmp = shell->tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	init(cmd);
	shell->cmds = cmd;
	while (tmp)
	{
		prev = tmp;
		if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd, shell);
		if (tmp == prev)
			tmp = tmp->next;
	}
}

void	create_token(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '|' )
	{
		add_token(shell, "|", PIPE);
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		add_token(shell, ">>", REDIRECT);
		(*i) += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(shell, ">", REDIRECT);
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(shell, "<<", HEREDOC);
		(*i) += 2;
	}
	else
		create_more(shell, input, i);
}

void	create_more(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '<')
	{
		add_token(shell, "<", REDIRECT);
		(*i)++;
	}
	else if (input[*i] == '\'')
	{
		add_token(shell, "'", SQUOTE);
		(*i)++;
	}
	else if (input[*i] == '"')
	{
		add_token(shell, "\"", DQUOTE);
		(*i)++;
	}
	else if (input[*i] == '$')
	{
		add_token(shell, "$", DOLLAR);
		(*i)++;
	}
}

