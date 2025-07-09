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
		//write(2, "Quit (core dumped)\n", 19);
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
		return NULL;
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
	return (free(dirs), full_path);
}

int	exec_external(t_cmd *cmd, char **args, char **envp)
{
	(void)cmd;
	pid_t	pid;
	int		status;
	char	*exe_path;

	if (!args[0] || args[0][0] == '\0')
	{
        ft_putendl_fd("bash: : command not found", STDERR_FILENO);
        return (127);
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
		return (127);
	}
	if (access(exe_path, X_OK) != 0)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
		free(exe_path);
		return (126);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(exe_path), 1);
	if (pid == 0)
	{
		// va liberata tutta la memoria 
		signal(SIGQUIT, signal_handler);
		execve(exe_path, args, envp);
		perror("execve");
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
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			g_status = 128 + WTERMSIG(status);
		}
	}
	free(exe_path);
	return (0);
}

void handle_heredoc(char *delimiter, char **envp, t_cmd *cmd, int *es)
{
    int hdoc_fd;
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
