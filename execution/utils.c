/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:14 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 00:16:20 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipe(t_shell *shell)
{
	char	*input;
	int		s;
	int		d;

	s = 0;
	d = 0;
	input = shell->input;
	shell->pipe = 0;
	while (*input)
	{
		if (*input == '\'' && d == 0)
			s = !s;
		else if (*input == '"' && s == 0)
			d = !d;
		else if (*input == '|' && s == 0 && d == 0)
			shell->pipe++;
		input++;
	}
	return (shell->pipe);
}

static void	free_single_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_arr(char **str, char **new)
{
	free_single_arr(str);
	free_single_arr(new);
}

char	**dup_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			free_arr(env, NULL);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_rmchar(char *str, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] != c)
			i++;
		j++;
	}
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			new[j++] = str[i];
		i++;
	}
	return (new[j] = '\0', new);
}
