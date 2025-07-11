/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:27 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 19:08:49 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_type2(t_token **tmp, t_cmd **cmd)
{
	t_cmd	*new_cmd;

	if (!tmp || !*tmp || !cmd || !*cmd)
		return ;
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

void	add_redir(t_redir **redir_list, char *filename, int type)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = malloc(sizeof(t_redir));
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
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

void	check_type(t_shell *shell, t_token **tmp, t_cmd *cmd, int *es)
{
	char	*expand;

	if ((*tmp)->type == WORD || (*tmp)->type == EOF)
	{
		if ((*tmp)->quote != '\'')
			expand = expand_var(shell, (*tmp)->value, es);
		else
			expand = ft_strdup((*tmp)->value);
		if (!expand)
			expand = ft_strdup("");
		cmd->argv = add_word(cmd->argv, expand);
		free(expand);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->type == REDIRECT && (*tmp)->next)
		check_redi(cmd, tmp);
	else if ((*tmp)->type == HEREDOC && (*tmp)->next)
	{
		add_redir(&cmd->redir, (*tmp)->next->value, HEREDOC);
		*tmp = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

void	check_redi(t_cmd *cmd, t_token **tmp)
{
	if (ft_strcmp((*tmp)->value, "<") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, INFILE);
	else if (ft_strcmp((*tmp)->value, ">") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, OUTFILE);
	else if (ft_strcmp((*tmp)->value, ">>") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, APPEND);
	*tmp = (*tmp)->next->next;
}

int	mult_redir(char *input)
{
	int		count;
	char	a;

	count = 1;
	a = *input;
	if (input[1] && input[1] != a && (input[1] == '<' || input[1] == '>'))
		return (1);
	while (input[count] && input[count] == a)
		count++;
	if (count > 2)
		return (1);
	return (0);
}
