/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:29:48 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/06 16:08:15 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sorter(int n, char **envp, int *idx)
{
	int	i;
	int	j;
	int	min;
	int	tmp;
	
	i = 0;
	while (i < n)
	{
		min = i;
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(envp[idx[min]], envp[idx[j]]) > 0)
				min = j;
			j++;
		}
		if (min != i)
		{
			tmp = idx[i];
			idx[i] = idx[min];
			idx[min] = tmp;
		}
		i++;
	}
}

int	*find_min(char **envp, int n)
{
	int	*idx;
	int	i;

	idx = malloc(sizeof(int) * n);
	if (!idx)
		return (NULL);
	i = -1;
	while (++i < n)
		idx[i] = i;
	i = 0;
	sorter(n, envp, idx);
	return (idx);
}

char	**dup_exp(char **envp)
{
	int		i;
	char	**env;
	int		*srt;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	srt = find_min(envp, i);
	if (!srt)
		return (free(env), NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[srt[i]]);
		if (!env[i])
			return (free_all(env, NULL), free(srt), NULL);
		i++;
	}
	env[i] = NULL;
	free(srt);
	return (env);
}

int	print_exp(char **str)
{
	int	i;
	int	j;
	char	**exp;

	i = 0;
	exp = dup_exp(str);
	if (!exp)
		return (1);
	while (exp[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (exp[i][j] != '=' && exp[i][j] != '\0')
			printf("%c", exp[i][j++]);
		if (exp[i][j] == '=')
			printf("=\"%s\"\n", &exp[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free_all(exp, NULL);
	return (0);
}

char	**ins_exp(char *str, char **envp)
{
	int	i;
	int	j;
	char **new;

	i = 0;
	while (envp[i])
		i++;
	j = check_same(str, envp);
	if (j != -1)
	{
		unset(envp, str);
		i--;
	}
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_all(envp, NULL);
	return (new);
}
