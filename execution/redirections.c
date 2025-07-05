/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/04 19:29:01 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == OUTFILE)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror("open"), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror("open"), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == INFILE)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd == -1)
				return (perror("open"), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
