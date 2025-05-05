/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:47:51 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/06 00:12:13 by kbossio          ###   ########.fr       */
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
		while (str[j] == envp[i][j] && str[j] != '=' && str[j] != '\0')
			j++;
		if ((str[j] == '=' || str[j] == '\0') && (envp[i][j] == '\0' || envp[i][j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

int	unset(char **envp, char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[n] != '=' && str[n] != '\0')
		n++;
	if (check_same(str, envp) != -1)
	{
		i = check_same(str, envp);
		free(envp[i]);
		while (envp[i] != NULL)
		{
			envp[i] = envp[i + 1];
			i++;
		}
		return (0);
	}
	return (1);
}
