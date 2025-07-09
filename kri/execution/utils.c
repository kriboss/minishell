/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:14 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/05 14:11:16 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arr(char **str, char **new)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
	if (new != NULL)
	{
		i = 0;
		while (new[i] != NULL)
		{
			free(new[i]);
			new[i] = NULL;
			i++;
		}
		free(new);
		new = NULL;
	}
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

int	ft_strcmp(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char )s2[i]);
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
