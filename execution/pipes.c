/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/12 13:15:18 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	connect_h(t_shell *shell, int pipe_fd[2], int *prev_fd)
{
	if (shell->cmds->next)
	{
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		if (*prev_fd != STDIN_FILENO)
			close(*prev_fd);
		*prev_fd = pipe_fd[0];
	}
	else
	{
		close_pipe(pipe_fd);
		if (*prev_fd != STDIN_FILENO)
			close(*prev_fd);
		*prev_fd = STDIN_FILENO;
	}
}

static int	fork_checks(t_shell *shell)
{
	shell->i = shell->i + 1;
	shell->pids[shell->i] = fork();
	if (shell->pids[shell->i] == -1)
		return (perror("fork"), -1);
	if (shell->pids[shell->i] > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (1);
}

static int	connect(t_shell *shell, char **envp, int pipe_fd[2], t_cmd *tmp)
{
	static int	prev_fd = STDIN_FILENO;

	if (fork_checks(shell) == -1)
		return (-1);
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
		envp = execute(shell, shell->cmds->argv, envp, tmp);
		shell->cmds = tmp;
		if (shell)
			free_all(shell);
		if (envp)
			free_matrix(envp);
		exit(shell->es);
	}
	connect_h(shell, pipe_fd, &prev_fd);
	return (0);
}

int	pipex(t_shell *shell, char **envp, int n)
{
	int		pipe_fd[2];
	t_cmd	*tmp;
	int		ok;

	tmp = shell->cmds;
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
	signla_status(shell, &ok, n);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	shell->cmds = tmp;
	return (pipex_exit(shell, ok), 0);
}

void	pipex_exit(t_shell *shell, int ok)
{
	if (ok == 130)
	{
		write(1, "\n", 1);
		shell->status = 130;
	}
	else if (ok == 131)
		shell->status = 131;
	else if (ft_strcmp(shell->cmds->argv[0], "exit") != 0)
		shell->status = 0;
}
