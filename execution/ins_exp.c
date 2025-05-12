/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:17:27 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/12 12:59:46 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_ins(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (printf("bash: export: `%s': not a valid identifier\n", str), 1);
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
	{
		if ((str[i] < '0' && str[i] > '9') || (str[i] < 'A' && str[i] > 'Z')
			|| (str[i] < 'a' && str[i] > 'z'))
		{
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ins_exp(char *str, char **envp)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;
	int		c;

	i = 0;
	c = 0;
	while (envp[i])
		i++;
	if (check_ins(str) == 1)
		return (envp);
	j = check_same(str, envp);
	if (j != -1)
	{
		if (ft_strchr(str, '+'))
		{
			tmp = ft_rmchar(str, '+');
			str = ft_strjoin(tmp, ft_strchr(str, '=') + 1);
			unset(envp, str);
			c = 1;
		}
		else
		{
			tmp = ft_rmchar(str, '=');
			unset(envp, tmp);
		}
		free(tmp);
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
	if (c == 1)
		free(str);
	return (new[i + 1] = NULL, free_all(envp, NULL), new);
}

char	**add_exp(char *str, char **envp)
{
	int		i;
	char	**new;

	i = 0;
	new = ft_split(str, ' ');
	if (!new)
		return (NULL);
	while (new[i])
	{
		if (check_ins(new[i]) == 0)
			envp = ins_exp(new[i], envp);
		i++;
	}
	return (free_all(new, NULL), envp);
}
