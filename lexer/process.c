/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:27 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/17 10:10:10 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void create_token(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '|' )
	{
		add_token(shell, "|", PIPE);
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
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
	else if (input[*i] == '<')
	{
		add_token(shell, "<", REDIRECT);
		(*i)++;
	}
}

void add_token(t_shell *shell, char *value, int type)
{
	t_token *new_token;

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

void tokenize(t_shell *shell)
{
	int i;
	char *input;

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
			int start = i;
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

void check_type(t_token **tmp, t_cmd *cmd)
{
	if ((*tmp)->type == WORD || (*tmp)->type == EOF)
	{
		cmd->argv = add_word(&cmd->argv, (*tmp)->value);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->type == REDIRECT && (*tmp)->next)
	{
		if (ft_strcmp((*tmp)->value, "<") == 0)
			cmd->infile = ft_strdup((*tmp)->next->value);
		else if (ft_strcmp((*tmp)->value, ">") == 0)
			cmd->outfile = ft_strdup((*tmp)->next->value);
		else if (ft_strcmp((*tmp)->value, ">>") == 0)
		{
			cmd->outfile = ft_strdup((*tmp)->next->value);
			cmd->append = 1;
		}
		*tmp = (*tmp)->next->next;
	}
	else if ((*tmp)->type == HEREDOC && (*tmp)->next)
	{
		cmd->delim = ft_strdup((*tmp)->next->value);
		cmd->heredoc = 1;
		*tmp = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

// ls -l | grep txt | wc -l
// linked list of t_cmd, cmd1 → cmd2 → cmd3

void check_type2(t_token **tmp, t_cmd **cmd)
{
	t_cmd *new_cmd;

	if (!tmp || !*tmp || !cmd || !*cmd)
	if ((*tmp)->type == PIPE)
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		init(new_cmd);
		(*cmd)->next = new_cmd;
		*cmd = new_cmd;
		*tmp = (*tmp)->next;
	}
}
