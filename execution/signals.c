/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:53 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/06 19:30:57 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nminishell> ");
		g_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		g_status = 131;
	}
}

void	start_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

static char	**get_path_dirs(char *envp[])
{
	char	*path_line;
	char	**dirs;

	path_line = NULL;
	while (*envp && !(path_line = ft_strnstr(*envp, "PATH=", 5)))
		envp++;
	if (!path_line)
		return (NULL);
	// salta "PATH="
	dirs = ft_split(path_line + 5, ':');
	return (dirs);
}

static char	*find_executable(char *cmd, char *envp[])
{
	char	**dirs;
	char	*full_path;
	char	*tmp;
	int		i;

	dirs = get_path_dirs(envp);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			break ;
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


int exec_external(char **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*exe_path;

	exe_path = find_executable(args[0], envp);
	if (!exe_path)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		free_all(args, NULL);
		return (127);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(exe_path), free_all(args, NULL), 1);
	if (pid == 0)
	{
		execve(exe_path, args, envp);
		return (perror("execve"), free(exe_path), free_all(args, NULL), 1);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	free(exe_path);
	free_all(args, NULL);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
