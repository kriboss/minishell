/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:14 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/03 12:34:48 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_min(char **envp, int i)
{
	int		j;
	int		min;

	min = i++;
	if (envp[0] == NULL)
		return (0);
	while (envp[i])
	{
		j = 0;
		if (envp[min][j] > envp[i][j])
			min = i;
		else if (envp[min][j] == envp[i][j])
		{
			while (envp[min][j] == envp[i][j])
				j++;
			if (envp[min][j] > envp[i][j])
				min = i;
		}
		i++;
	}
	return (min);
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
		env[i] = ft_strdup(envp[find_min(envp, i)]);
		if (!env[i])
			return (free(env), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	print_exp(char **str)
{
	int	i;
	int	j;
	char	**exp;

	i = 0;
	exp = dup_env(str);
	while (exp[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (exp[i][j] != '=' && exp[i][j] != '\0')
			printf("%c", exp[i][j++]);
		if (exp[i][j] == '=' && exp[i][j + 1] != '\0')
			printf("\"%s\"\n", &exp[i][j + 1]);
		i++;
	}
	free(exp);
	return (0);
}