/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/13 11:43:35 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	red_out(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	red_in(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	return (0);
}

int	red_app(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	handle_red(char **cmds, char **envp)
{
	int	i;

	i = 0;
	(void)envp;
	while (cmds[i])
	{
		if (ft_strnstr(cmds[i], ">>", 2))
		{
			if (red_app(cmds[i + 1]) == 1)
				return (1);
			cmds[i] = NULL;
		}
		else if (ft_strnstr(cmds[i], ">", 1))
		{
			if (red_out(cmds[i + 1]) == 1)
				return (1);
			cmds[i] = NULL;
		}
		else if (ft_strnstr(cmds[i], "<", 1))
		{
			if (red_in(cmds[i + 1]) == 1)
				return (1);
			cmds[i] = NULL;
		}
		i++;
	}
	free_all(cmds, NULL);
	return (0);
}
