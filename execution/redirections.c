/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/09 13:43:41 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_outfile_redir(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append_redir(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_infile_redir(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_heredoc_redir(const char *filename)
{
	int	fd;

	fd = ft_atoi(filename);
	if (fd <= 0)
	{
		perror("invalid heredoc fd");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == OUTFILE && handle_outfile_redir(redir->filename))
			return (1);
		else if (redir->type == APPEND && handle_append_redir(redir->filename))
			return (1);
		else if (redir->type == INFILE && handle_infile_redir(redir->filename))
			return (1);
		else if (redir->type == HEREDOC
			&& handle_heredoc_redir(redir->filename))
			return (1);
		redir = redir->next;
	}
	return (0);
}
