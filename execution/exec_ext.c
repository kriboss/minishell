/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:04:21 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/12 13:01:42 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_exe(char **args, char **envp)
{
	char	*exe_path;

	exe_path = find_executable(args[0], envp);
	if (!exe_path)
	{
		if (ft_strchr(args[0], '/'))
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		free(exe_path);
		return (NULL);
	}
	return (exe_path);
}

int	exec_child(t_shell *shell, char *exe_path, t_fd *t)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close(t->input);
	close(t->output);
	execve(exe_path, shell->cmds->argv, shell->envp);
	perror("execve");
	free_all(shell);
	exit(1);
}

void	exec_parent(t_shell *shell, int pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (waitpid(pid, &status, 0) == -1)
		;
	signal(SIGINT, signal_handler);
	if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		shell->status = 128 + WTERMSIG(status);
	}
}

void	exec_pipe(t_shell *shell, char *exe_path, char **envp, t_fd *t)
{
	signal(SIGQUIT, SIG_DFL);
	execve(exe_path, shell->cmds->argv, envp);
	perror("execve");
	close(t->input);
	close(t->output);
	free_all(shell);
	exit(1);
}

int	exec_external(t_shell *shell, char **args, char **envp, t_fd *t)
{
	int		pid;
	int		i;
	char	*exe_path;

	i = check_before_exe(args);
	if (i != 0)
		return (i);
	exe_path = check_exe(args, envp);
	if (!exe_path)
		return (127);
	if (shell->pipe == 0)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), free(exe_path), 1);
		if (pid == 0)
			exec_child(shell, exe_path, t);
		else
			exec_parent(shell, pid);
	}
	else
		exec_pipe(shell, exe_path, envp, t);
	free(exe_path);
	return (0);
}
