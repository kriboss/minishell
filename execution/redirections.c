/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 09:26:27 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_output_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == OUTFILE)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_input_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == INFILE)
	{
		fd = open(redir->filename, O_RDONLY);
		if (fd == -1)
			return (perror("open"), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == HEREDOC)
	{
		fd = ft_atoi(redir->filename);
		if (fd <= 0)
		{
			perror("invalid heredoc fd");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	process_single_redir(t_redir *redir)
{
	if (redir->type == OUTFILE || redir->type == APPEND)
		return (handle_output_redir(redir));
	else if (redir->type == INFILE || redir->type == HEREDOC)
		return (handle_input_redir(redir));
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (process_single_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	close_fd(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
