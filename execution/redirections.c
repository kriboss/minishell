/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/06/16 09:54:44 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	red_out(t_shell *shell, char **cmds, char **envp)
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
	execute(shell, tmp, envp);
	close(fd);
	return (0);
}

int	red_in(char **cmds)
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

int	red_app(char **cmds)
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

