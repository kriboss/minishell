/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:17:27 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/05 13:28:22 by sara             ###   ########.fr       */
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
			|| (str[i] < 'a' && str[i] > 'z')
			|| (str[i] == '+' && str[i + 1] != '='))
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
		if (strchr(str[i], '\"'))
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
	return (new[i + 1] = NULL, new);//free old, return new
}

char	**add_exp(char **str, char **envp)
{
	int		i;
	int		j;
	char	**old_env;
	char	**new_env;
	char	*val;
	char	*tmp;

	i = 0;
	new_env = dup_env(envp);//
	if (!new_env)
		return (NULL);
	while (str[i])
	{
		if (check_ins(str[i]) == 0)
		{
			j = check_same(str[i], new_env);
			if (j != -1)
			{
				if (ft_strchr(str[i], '+'))
				{
					val = ft_strchr(str[i], '=');
					if (val)
					{
						if (ft_strchr(new_env[j], '='))
							val++;
						tmp = ft_strjoin(new_env[j], val);
						if (tmp)
						{
							free(new_env[j]);
							new_env[j] = tmp;
						}
					}
				}
				else if (ft_strchr(str[i], '='))
				{
					free(new_env[j]);
					new_env[j] = ft_strdup(str[i]);
				}
			}
			else
			{
				old_env = new_env;
				new_env = ins_exp(str[i], new_env);
				free_arr(old_env, NULL);
			}
		}
		i++;
	}
	return (new_env);//return new allocated
}
