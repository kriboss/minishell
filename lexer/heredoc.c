/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:13:11 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 19:08:39 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_heredoc(t_shell *shell, t_hd *hd, const char *delimiter, int *es)
{
	hd->delimiter = delimiter;
	hd->envp = shell->envp;
	hd->es = es;
	if (pipe(hd->pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	hd->stdin_backup = dup(STDIN_FILENO);
	shell->status = 0;
	signal(SIGINT, heredoc_sig);
	return (0);
}

int	cleanup_heredoc_resources(t_hd *hd, char *line)
{
	close(hd->pipefd[1]);
	close(hd->pipefd[0]);
	if (line)
		free(line);
	dup2(hd->stdin_backup, STDIN_FILENO);
	close(hd->stdin_backup);
	signal(SIGINT, signal_handler);
	rl_done = 0;
	return (-1);
}

static int	finalize_heredoc_pipe(t_hd *hd)
{
	close(hd->pipefd[1]);
	dup2(hd->stdin_backup, STDIN_FILENO);
	close(hd->stdin_backup);
	signal(SIGINT, signal_handler);
	rl_done = 0;
	return (hd->pipefd[0]);
}

static int	process_heredoc_line(t_shell *shell, char *line, t_hd *hd)
{
	char	*expand;

	if (shell->status == 130 || !line)
	{
		if (shell->status == 130)
			return (cleanup_heredoc_resources(hd, line));
		free(line);
		return (1);
	}
	if (ft_strcmp(line, hd->delimiter) == 0)
	{
		free(line);
		return (1);
	}
	expand = expand_var(shell, line, hd->es);
	if (!expand)
		return (cleanup_heredoc_resources(hd, line));
	write(hd->pipefd[1], expand, ft_strlen(expand));
	write(hd->pipefd[1], "\n", 1);
	free(line);
	free(expand);
	return (0);
}

int	heredoc_pipe(t_shell *shell, const char *delimiter, int *es)
{
	t_hd		hd;
	char		*line;
	int			result;

	if (init_heredoc(shell, &hd, delimiter, es) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		update_status_code(shell);
		result = process_heredoc_line(shell, line, &hd);
		if (result == -1)
			return (-1);
		if (result == 1)
			break ;
	}
	return (finalize_heredoc_pipe(&hd));
}
