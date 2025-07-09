/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:27 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/04 11:02:50 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ls -l | grep txt | wc -l
// linked list of t_cmd, cmd1 → cmd2 → cmd3

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
