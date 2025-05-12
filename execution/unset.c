/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/12 12:57:19 by kbossio          ###   ########.fr       */
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

int	unset(char **envp, char *str)
{
	int		i;
	int		n;
	char	**tmp;

	n = 0;
	if (str == NULL)
		return (1);
	tmp = ft_split(str, ' ');
	if (tmp == NULL)
		return (1);
	while (tmp[n])
	{
		if (match_word(tmp[n], envp) != -1)
		{
			i = match_word(tmp[n], envp);
			free(envp[i]);
			while (envp[i] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
		}
		n++;
	}
	return (free_all(tmp, NULL), 0);
}
