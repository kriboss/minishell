/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/04 19:01:31 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_token(const char *input, int start, int end)
{
	char	*out;
	int		i;
	int		j;

	i = start;
	j = 0;
	out = malloc(end - start + 1);
	while (i < end)
		out[j++] = input[i++];
	out[j] = '\0';
	return (out);
}

void	tokenize(t_shell *shell)
{
	int		i;
	char	*input;
	int		start;
	char	*word;

	i = 0;
	input = shell->input;
	while (input[i] && is_space(input[i]))
		i++;
	while (input[i])
	{
		if (is_special(input[i]))
			handle_special(shell, input, &i);
		else if (is_word(input[i]))
		{
			start = i;
			while (input[i] && is_word(input[i]))
				i++;
			word = ft_substr(input, start, i - start);
			add_token(shell, word, WORD, 0);
			free(word);
		}
		while (input[i] && is_space(input[i]))
			i++;
	}
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

void	tok_cmd(t_shell *shell, char **envp)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*tmp;
	t_token	*prev;

	tmp = shell->tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	init(cmd);
	head = cmd;
	shell->cmds = cmd;
	while (tmp)
	{
		prev = tmp;
		if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd, envp);
		if (tmp == prev)
			tmp = tmp->next;
	}
	shell->cmds = head;
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
