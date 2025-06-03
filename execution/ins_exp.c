/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:17:27 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/13 18:09:00 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_ins(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (printf("bash: export: `%s': not a valid identifier\n", str), 1);
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((str[i] < '0' && str[i] > '9') || (str[i] < 'A' && str[i] > 'Z')
			|| (str[i] < 'a' && str[i] > 'z') || (str[i] == '+' && str[i + 1] != '='))
		{
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**rm_quotes(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (strchr(str[i], '\''))
		{
			tmp = str[i];
			str[i] = ft_rmchar(tmp, '\'');
			free(tmp);
		}
		else if (strchr(str[i], '\"'))
		{
			tmp = str[i];
			str[i] = ft_rmchar(tmp, '\"');
			free(tmp);
		}
		i++;
	}
	return (str);
}

char	**ins_exp(char *str, char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	return (new[i + 1] = NULL, free_arr(envp, NULL), new);
}

char	**add_exp(char **str, char **envp)
{
	int		i;
	int		j;

	i = 0;
	str = rm_quotes(str);
	while (str[i])
	{
		if (check_ins(str[i]) == 0)
		{
			j = check_same(str[i], envp);
			if (j != -1)
			{
				if (ft_strchr(str[i], '+'))
				{
					if (ft_strchr(envp[j], '='))
						envp[j] = ft_strjoin(envp[j], ft_strchr(str[i], '=') + 1);
					else
						envp[j] = ft_strjoin(envp[j], ft_strchr(str[i], '='));
					unset(&str[i], envp);
				}
				else if (ft_strchr(str[i], '='))
				{
					free(envp[j]);
					envp[j] = ft_strdup(str[i]);
				}
			}
			else
				envp = ins_exp(str[i], envp);
		}
		i++;
	}
	return (envp);
}
