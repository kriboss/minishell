/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/26 16:39:18 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *extract_token(const char *input, int start, int end)
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
    return out;
}

void	tokenize(t_shell *shell)
{
	int		i = 0;
	char	*input = shell->input;

	while (input[i] && is_space(input[i]))
		i++;
	while (input[i])
	{
		if (is_space(input[i]))
			while (input[i] && is_space(input[i])) i++;

		else if (input[i] == '\'' || input[i] == '"')
		{
			char quote = input[i++];
			int start = i;
			while (input[i] && input[i] != quote)
				i++;
			char *word = ft_substr(input, start, i - start);
			add_token(shell, word, WORD);
			free(word);
			if (input[i] == quote)
				i++;
		}
		else if (is_special(input[i]))
			create_token(shell, input, &i);
		else if (is_word(input[i]))
		{
			int start = i;
			while (input[i] && is_word(input[i]))
				i++;
			char *word = extract_token(input, start, i);
			add_token(shell, word, WORD);
			free(word);
		}
		else
			i++;
	}
}

/* void	tokenize(t_shell *shell)
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
			create_token(shell, input, &i);
		else if (is_word(input[i]))
		{
			start = i;
			while (input[i] && is_word(input[i]))
				i++;
			char *word = extract_token(input, start, i);
			add_token(shell, word, WORD);
			free(word);
		}
		else if (is_space(input[i]))
		{
			while (input[i] && is_space(input[i]))
				i++;
		}
		else
			i++;
	}
} */

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
			check_type(&tmp, cmd);
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
	else if (input[*i] == '$')
	{
		add_token(shell, "$", DOLLAR);
		(*i)++;
	}
}
