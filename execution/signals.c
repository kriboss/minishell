/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:53 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/09 19:10:40 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//6
int	g_status = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_status = 131;
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

int	check_cmd(char *cmd)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (1);
	while (cmd[i] && (cmd[i] == '/' || cmd[i] == '.'))
		i++;
	if (cmd[i] == '\0')
		return (1);
	return (0);
}
char	*check_dir(char **dirs, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			full_path = NULL;
			return (NULL);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (NULL);
}

static char	*find_executable(char *cmd, char *envp[])
{
	char	**dirs;
	char	*full_path;


	if (check_cmd(cmd) == 1)
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
	full_path = check_dir(dirs, cmd);
	return (free_arr(dirs, NULL), full_path);
}

int	check_exe(char *exe_path, char **args)
{
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
		return (127);
	}
	if (access(exe_path, X_OK) != 0)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
		free(exe_path);
		return (126);
	}
	return (0);
}

void	check_sig(pid_t pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (waitpid(pid, &status, 0) == -1)
		;
	signal(SIGINT, signal_handler);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		g_status = 128 + WTERMSIG(status);
	}
}

int	check_args(char **args)
{
	if (!args[0] || args[0][0] == '\0')
	{
		ft_putendl_fd("bash: : command not found", STDERR_FILENO);
		return (127);
	}
	return (0);
}

int	exec_external(char **args, char **envp)
{
	pid_t	pid;
	char	*exe_path;
	int		i;

	if (check_args(args) == 127)
		return (127);
	exe_path = find_executable(args[0], envp);
	i = check_exe(exe_path, args);
	if (i != 0)
		return (i);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(exe_path), 1);
	if (pid == 0)
	{
		signal(SIGQUIT, signal_handler);
		execve(exe_path, args, envp);
		perror("execve");
		exit(1);
	}
	else
		check_sig(pid);
	return (free(exe_path), 0);
}

void	handle_heredoc(char *delimiter, char **envp, t_cmd *cmd, int *es)
{
	int		hdoc_fd;
	char	*fd_str;

	hdoc_fd = heredoc_pipe(delimiter, envp, es);
	if (hdoc_fd < 0)
	{
		perror("heredoc pipe error");
		exit(1);
	}
	fd_str = ft_itoa(hdoc_fd);
	add_redir(&cmd->redir, fd_str, HEREDOC);
	free(fd_str);
}
