/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/21 11:29:53 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	red_out(char **cmds, char **envp)
{
	int	fd;
	int	i;
	char **tmp;

	i = 0;
	while (cmds[i])
		i++;
	fd = open(cmds[--i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	tmp = malloc(sizeof(char *) * (--i));
	tmp[i] = NULL;
	while (--i >= 0)
	{
		tmp[i] = ft_strdup(cmds[i]);
	}
	execute(tmp, envp);
	close(fd);
	return (0);
}

int	red_in(char **cmds, char **envp)
{
	int	fd;
	int	i;
	
	i = 0;
	while (cmds[i])
		i++;
	fd = open(cmds[--i], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	return (0);
}

int	red_app(char **cmds, char **envp)
{
	int	fd;
	int	i;
	
	i = 0;
	while (cmds[i])
		i++;
	fd = open(cmds[--i], O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	/*
	if (ft_strrchr(cmds[i], ''))
	{
		if (red_app(cmds[i + 1]) == 1)
			return (1);
		cmds[i] = NULL;
	}
	*/
	if (ft_strrchr(cmds[i], '>'))
	{
		if (red_out(cmds, envp) == 1)
			return (1);
		cmds[i] = NULL;
	}
	else if (ft_strnstr(cmds[i], "<", 1))
	{
		if (red_in(cmds[i + 1], envp) == 1)
			return (1);
		cmds[i] = NULL;
	}
	// free_all(cmds, NULL);
	return (0);
}
