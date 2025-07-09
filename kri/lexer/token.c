/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/09 13:31:38 by sel-khao         ###   ########.fr       */
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

void    tokenize(t_shell *shell)
{
	int     i;
	char    *input;
	int     start;
	char    *no_quote;
	char    *word;
	char    quote_type;

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
			while (input[i] && (is_word(input[i]) || in_quotes(input, i)))
				i++;
			word = ft_substr(input, start, i - start);
			quote_type = 0;
			if (strchr(word, '\''))
				quote_type = '\'';
			else if (strchr(word, '"'))
				quote_type = '"';
			no_quote = process_quotes(word);
			add_token(shell, no_quote, WORD, quote_type);
			free(word);
			free(no_quote);
		}
		while (input[i] && is_space(input[i]))
			i++;
	}
}

char *process_quotes(char *word)
{
	char	*result;
	int     i;
	int     j;
	char	quote;
		
	result = malloc(strlen(word) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			quote = word[i++];
			while (word[i] && word[i] != quote)
				result[j++] = word[i++];
			if (word[i] == quote)
				i++;
		}
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
	return (result);
}

int in_quotes(char *input, int pos)
{
	int i = 0;
	char current_quote = 0;
		
	while (i < pos)
	{
		if ((input[i] == '\'' || input[i] == '"') && current_quote == 0)
			current_quote = input[i];
		else if (input[i] == current_quote)
			current_quote = 0;
		i++;
	}
	return (current_quote != 0);
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
		if (tmp->type == HEREDOC)
			check_delim(&tmp, envp, cmd);
		else if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd, envp);
		if (tmp == prev)
			tmp = tmp->next;
	}
	shell->cmds = head;
}

void check_delim(t_token **tmp, char **envp, t_cmd *cmd)
{
    t_token *delim;
    char *delimiter;

    delim = (*tmp)->next;
    if (delim)
    {
        delimiter = delim->value;
        handle_heredoc(delimiter, envp, cmd);
        *tmp = (*tmp)->next->next;
    }
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
