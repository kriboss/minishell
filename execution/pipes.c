/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/04 18:49:41 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	connect(t_shell *shell, char **envp, int pipe_fd[2])
{
	static int	prev_fd;
	pid_t		pid;

	prev_fd = STDIN_FILENO;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (prev_fd != STDIN_FILENO)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (shell->cmds->next)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute(shell, shell->cmds->argv, envp);
		exit(1);
	}
	if (shell->cmds->next)
		close(pipe_fd[1]);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	prev_fd = pipe_fd[0];
	if (!shell->cmds->next)
		prev_fd = STDIN_FILENO;
	return (0);
}

int	pipex(t_shell *shell, char **envp)
{
	int		i;
	int		n;
	int		pipe_fd[2];
	t_cmd	*tmp;

	tmp = shell->cmds;
	n = 0;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	i = 0;
	while (shell->cmds)
	{
		if (shell->cmds)
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), 1);
		if (connect(shell, envp, pipe_fd) == -1)
			return (1);
		shell->cmds = shell->cmds->next;
	}
	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
