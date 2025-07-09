/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/13 17:14:06 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_same(char *str, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (str[j] == envp[i][j] && str[j] != '+'
			&& str[j] != '=' && str[j] != '\0')
			j++;
		if ((str[j] == '=' || str[j] == '\0' || str[j] == '+')
			&& (envp[i][j] == '\0' || envp[i][j] == '=' || envp[i][j] == '+'))
			return (i);
		i++;
	}
	return (-1);
}

int	match_word(char *str, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (str[j] == envp[i][j] && str[j] != '\0')
			j++;
		if (str[j] == '\0' && (envp[i][j] == '=' || envp[i][j] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	unset(char **str, char **envp)
{
	int		i;
	int		n;

	n = 0;
	if (str == NULL)
		return (1);
	while (str[n])
	{
		if (match_word(str[n], envp) != -1)
		{
			i = match_word(str[n], envp);
			free(envp[i]);
			while (envp[i] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
		}
		n++;
	}
	return (0);
}
