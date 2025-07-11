/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:53 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 19:38:49 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_status = SIGQUIT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	start_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static char	**get_path_dirs(char *envp[])
{
	char	**dirs;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	dirs = ft_split(ft_strnstr(*envp, "PATH=", 5) + 5, ':');
	return (dirs);
}

static char	*find_executable(char *cmd, char *envp[])
{
	char	**dirs;
	char	*full_path;
	char	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	dirs = get_path_dirs(envp);
	if (!dirs)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				break ;
			free(full_path);
			full_path = NULL;
			break ;
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (full_path);
}

int	exec_external(t_shell *shell, char **args, char **envp, t_fd *t)
{
	int		pid;
	int		fd;
	int		status;
	char	*exe_path;

	if (!args[0] || args[0][0] == '\0')
	{
		ft_putendl_fd("bash: : command not found", STDERR_FILENO);
		return (127);
	}
	fd = open(args[0], __O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
		close(fd);
		return (126);
	}
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
		return (127);
	}
	if (shell->pipe == 0)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), free(exe_path), 1);
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			close(t->input);
			close(t->output);
			execve(exe_path, args, envp);
			perror("execve");
			free_all(shell);
			exit(1);
		}
		else
		{
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
	}
	else
	{
		signal(SIGQUIT, signal_handler);
		execve(exe_path, args, envp);
		perror("execve");
		close(t->input);
		close(t->output);
		free_all(shell);
		exit(1);
	}
	free(exe_path);
	return (0);
}
