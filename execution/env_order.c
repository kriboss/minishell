/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:27:25 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 09:12:48 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**order_env(char **envp)
{
	char	**export;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	export = matrix_dup(envp);
	while (++j < matrix_len(envp))
	{
		i = 0;
		while (i < matrix_len(envp) - 1)
		{
			if (ft_strncmp(export[i], export[i + 1], ft_strlen(export[i])) >= 0)
			{
				tmp = export[i];
				export[i] = ft_strdup(export[i + 1]);
				free(export[i + 1]);
				export[i + 1] = ft_strdup(tmp);
				free(tmp);
			}
			i++;
		}
	}
	return (export);
}

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**matrix_dup(char **old_mtx)
{
	char	**new_mtx;
	int		j;

	j = 0;
	new_mtx = (char **)malloc(sizeof(char *) * (matrix_len(old_mtx) + 1));
	if (new_mtx == NULL)
		return (NULL);
	while (old_mtx[j])
	{
		new_mtx[j] = ft_strdup(old_mtx[j]);
		j++;
	}
	new_mtx[j] = NULL;
	return (new_mtx);
}

void	free_matrix(char **matrix)
{
	int	j;

	j = 0;
	while (matrix[j])
	{
		free(matrix[j]);
		j++;
	}
	free(matrix);
}

void	close_pipe(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (pipe_fd[1] != -1)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}
