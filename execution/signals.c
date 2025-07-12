/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:53 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/12 13:01:15 by sel-khao         ###   ########.fr       */
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

char	**get_path_dirs(char *envp[])
{
	char	**dirs;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	dirs = ft_split(ft_strnstr(*envp, "PATH=", 5) + 5, ':');
	return (dirs);
}

char	*find_executable(char *cmd, char *envp[])
{
	char	**dirs;
	char	*full_path;
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
	do_access(&full_path, cmd, dirs);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (full_path);
}

void	do_access(char **full_path, char *cmd, char **dirs)
{
	int		i;
	char	*tmp;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path[0] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path[0], F_OK) == 0)
		{
			if (access(full_path[0], X_OK) == 0)
				break ;
			free(full_path[0]);
			full_path[0] = NULL;
			break ;
		}
		free(full_path[0]);
		full_path[0] = NULL;
		i++;
	}
}
