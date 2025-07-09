/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/09 19:03:40 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	connect(t_shell *shell, char **envp, int pipe_fd[2], t_cmd *tmp)
{
	static int	prev_fd = STDIN_FILENO;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
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
		shell->cmds = tmp;
		if (shell)
            free_all(shell);
        if (envp)
            free_arr(envp, NULL);
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
	int		n;
	int		pipe_fd[2];
	t_cmd	*tmp;
	int		ok;
	int		status;
	
	ok = 0;
	tmp = shell->cmds;
	n = 0;
	while (shell->cmds)
	{
		if (shell->cmds)
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), 1);
		if (connect(shell, envp, pipe_fd, tmp) == -1)
			return (1);
		shell->cmds = shell->cmds->next;
		n++;
	}
	while (n-- > 0)
	{
		wait(&status);
		if ((WIFEXITED(status) && WEXITSTATUS(status) == 130) ||
			(WIFSIGNALED(status) && WTERMSIG(status) == 130))
			ok = 130;
		else if ((WIFEXITED(status) && WEXITSTATUS(status) == 131) ||
			(WIFSIGNALED(status) && WTERMSIG(status) == 131))
			ok = 131;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	shell->cmds = tmp;
	if (ok == 130)
	{
		write(1, "\n", 1);
		g_status = 130;
	}
	else if (ok == 131)
		g_status = 131;
	else if (ft_strcmp(shell->cmds->argv[0], "exit") != 0)
		g_status = 0;
	return (0);
}
