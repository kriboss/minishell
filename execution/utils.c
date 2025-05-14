/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:14 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/13 10:41:50 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all(char **str, char **new)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	if (new != NULL)
	{
		i = 0;
		while (new[i] != NULL)
		{
			free(new[i]);
			i++;
		}
		free(new);
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
			return (free_all(env, NULL), NULL);
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
	{
		i++;
	}
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

char	**exec_split(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j++;
		i++;
	}
	new = malloc(sizeof(char *) * (j + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			k++;
		else
			new[k] = ft_strjoin(str + i, " ");
		while (str[i] != c && str[i] != '\0')
			i++;
		while (str[i] == c)
			i++;
	}
	new[k + 1] = NULL;
	return (new);
}
