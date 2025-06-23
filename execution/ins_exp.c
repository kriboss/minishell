/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:17:27 by kbossio           #+#    #+#             */
/*   Updated: 2025/06/23 08:33:57 by sel-khao         ###   ########.fr       */
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
	char **new_env;
	char *val;
	char *tmp;

	i = 0;
	new_env = dup_env(envp);//duplico per non lavorare sull'originale
	if(!new_env)
		return NULL;
	str = rm_quotes(str);
	while (str[i])
	{
		if (check_ins(str[i]) == 0)//se name valid
		{
			j = check_same(str[i], new_env);
			if (j != -1)//se esiste gia'
			{
				if (ft_strchr(str[i], '+'))//if +=value
				{
					val = ft_strchr(str[i], '=');//se = e vai oltre
					if (val)
					{
						val++;
						tmp = ft_strjoin(new_env[j], val);
						if (tmp)
						{
							free(new_env[j]);
							new_env[j] = tmp;
						}
					}
				}
				else if (ft_strchr(str[i], '='))//se solo var=value
				{
					free(new_env[j]);
					new_env[j] = ft_strdup(str[i]); // sostituisco
				}
			}
			else//se e' solo export VAR, do noting
				new_env = ins_exp(str[i], new_env);
		}
		i++;
	}
	return (new_env);
}
