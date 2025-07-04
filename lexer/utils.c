/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:38 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/04 18:29:48 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_word(char c)
{
	if (is_space(c) || is_special(c))
		return (0);
	return (1);
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

void	ft_readline(t_shell *shell)
{
	shell->input = readline("mininshell> ");
	if (!shell->input)
	{
		free_all(shell);
		exit(0);
	}
	if (shell->input[0])
		add_history(shell->input);
}

void	init(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
}

char	*extract_quoted(char *input, int *i)
{
	char	quote;
	int		j;
	int		len;
	char	*buffer;

	quote = input[*i];
	j = *i + 1;
	len = 0;
	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		return (NULL);
	while (input[j] && input[j] != quote)
	{
		if (quote == '"' && input[j] == '\\' && input[j + 1])
		{
			if (input[j + 1] == '"' || input[j + 1] == '\\'
				|| input[j + 1] == '$')
				buffer[len++] = input[++j];
			else
				buffer[len++] = input[j];
			j++;
		}
		else
			buffer[len++] = input[j++];
	}
	if (!input[j] || input[j] != quote)
	{
		free(buffer);
		printf("syntax error: unclosed quote\n");
		return (NULL);
	}
	buffer[len] = '\0';
	*i = j + 1;
	return (buffer);
}

void	handle_special(t_shell *shell, char *input, int *i)
{
	char	*quoted_str;
	char	quote;
	char	*var_token;
	int		start;

	quote = input[*i];
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quoted_str = extract_quoted(input, i);
		if (!quoted_str)
			return ;
		add_token(shell, quoted_str, WORD, quote);
		free(quoted_str);
	}
	else if (input[*i] == '$')
	{
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
	else
		create_token(shell, input, i);
}
