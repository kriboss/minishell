/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/12 12:51:31 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	connect(int i, char **cmds, char **envp, int pipe_fd[2])
{
	static int	prev_fd = STDIN_FILENO;
	pid_t		pid;

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
		if (cmds[i + 1])
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute(cmds[i], envp);
		exit(1);
	}
	if (cmds[i + 1])
		close(pipe_fd[1]);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	prev_fd = pipe_fd[0];
	if (!cmds[i + 1])
		prev_fd = STDIN_FILENO;
	return (0);
}

int	pipex(char **cmds, char **envp)
{
	int		i;
	int		n;
	int		pipe_fd[2];
	char	*old;

	n = 0;
	while (cmds[n])
	{
		old = cmds[n];
		cmds[n] = ft_strtrim(old, " \t\n");
		free(old);
		n++;
	}
	i = 0;
	while (i < n)
	{
		if (i < n - 1)
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), 1);
		if (connect(i, cmds, envp, pipe_fd) == -1)
			return (1);
		i++;
	}
	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
	free_all(cmds, NULL);
	return (0);
}
