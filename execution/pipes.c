/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 18:44:20 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	connect(t_shell *shell, char **envp, int pipe_fd[2], t_cmd *tmp)
{
	static int	prev_fd = STDIN_FILENO;

	shell->i = shell->i + 1;
	shell->pids[shell->i] = fork();
	if (shell->pids[shell->i] == -1)
		return (perror("fork"), -1);
	if (shell->pids[shell->i] > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (shell->pids[shell->i] == 0)
	{
		if (prev_fd != STDIN_FILENO)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (shell->cmds->next && pipe_fd[1] != -1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		close_fd();
		execute(shell, shell->cmds->argv, envp);
		shell->cmds = tmp;
		if (shell)
			free_all(shell);
		if (envp)
			free_arr(envp, NULL);
		exit(shell->es);
	}
	if (shell->cmds->next)
	{
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipe_fd[0];
	}
	else
	{
		close_pipe(pipe_fd);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = STDIN_FILENO;
	}
	return (0);
}

int	pipex(t_shell *shell, char **envp)
{
	int		n;
	int		i;
	int		pipe_fd[2];
	t_cmd	*tmp;
	int		ok;
	int		status;

	status = 0;
	ok = 0;
	tmp = shell->cmds;
	n = 0;
	shell->i = -1;
	while (shell->cmds)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (shell->cmds->next)
		{
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), 1);
		}
		if (connect(shell, envp, pipe_fd, tmp) == -1)
			return (1);
		shell->cmds = shell->cmds->next;
		n++;
	}
	i = 0;
	while (i < n)
	{
		waitpid(shell->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == 130)
			ok = 130;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 131)
			ok = 131;
		if (WIFEXITED(status))
			shell->es = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	shell->cmds = tmp;
	if (ok == 130)
	{
		write(1, "\n", 1);
		shell->status = 130;
	}
	else if (ok == 131)
		shell->status = 131;
	else if (ft_strcmp(shell->cmds->argv[0], "exit") != 0)
		shell->status = 0;
	return (0);
}
