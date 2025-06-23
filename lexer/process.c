/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:27 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/23 13:12:05 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_token(t_shell *shell, char *value, int type)
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

char	*extract_quoted(char *input, int *i)
{
	char	quote = input[*i];
	int		j = *i + 1;
	int		len = 0;
	char	*buffer = malloc(ft_strlen(input) + 1); // worst-case alloc

	if (!buffer)
		return (NULL);
	while (input[j] && input[j] != quote)
	{
		if (quote == '"' && input[j] == '\\' && input[j + 1])
		{
			if (input[j + 1] == '"' || input[j + 1] == '\\' ||
				input[j + 1] == '$')
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
	*i = j + 1;//sposto index dopo virgola di chiusura
	return (buffer);
}

void	handle_special(t_shell *shell, char *input, int *i)
{
	char *quoted_str;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		quoted_str = extract_quoted(input, i);
		if (!quoted_str)
			return ;
		add_token(shell, quoted_str, WORD);
		free(quoted_str);
	}
	else if (input[*i] == '$')
	{
		add_token(shell, "$", DOLLAR);
		(*i)++;
	}
	else
		create_token(shell, input, i);
}

void	tokenize(t_shell *shell)
{
	int i;
	char *input;
	int start;

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

char *expand_var(t_env *env_list, const char *input)
{
	
}

void	check_type(t_token **tmp, t_cmd *cmd, t_shell *shell)
{
	char *expand;
	
	if ((*tmp)->type == WORD || (*tmp)->type == EOF)
	{
		expand = expand_var(shell->envs, (*tmp)->value);
		cmd->argv = add_word(cmd->argv, expand);
		free(expand);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->type == REDIRECT && (*tmp)->next)
	{
		if (ft_strcmp((*tmp)->value, "<") == 0)
			add_redir(&cmd->redir, (*tmp)->next->value, INFILE);
		else if (ft_strcmp((*tmp)->value, ">") == 0)
			add_redir(&cmd->redir, (*tmp)->next->value, OUTFILE);
		else if (ft_strcmp((*tmp)->value, ">>") == 0)
			add_redir(&cmd->redir, (*tmp)->next->value, APPEND);
		*tmp = (*tmp)->next->next;
	}
	else if ((*tmp)->type == HEREDOC && (*tmp)->next)
	{
		add_redir(&cmd->redir, (*tmp)->next->value, HDOC);
		*tmp = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

// ls -l | grep txt | wc -l
// linked list of t_cmd, cmd1 → cmd2 → cmd3

void	check_type2(t_token **tmp, t_cmd **cmd)
{
	t_cmd *new_cmd;

	if (!tmp || !*tmp || !cmd || !*cmd)
		return ; //exit(EXIT_FAILURE);
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
		*cmd = new_cmd;//move foward
		*tmp = (*tmp)->next;//skip pipe
	}
}

void	add_redir(t_redir **redir_list, char *filename, int type)
{
	t_redir *new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_redir->filename = strdup(filename);
	new_redir->type = type;
	new_redir->next = NULL;
	if (!*redir_list)
		*redir_list = new_redir;
	else
	{
		t_redir *tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}
