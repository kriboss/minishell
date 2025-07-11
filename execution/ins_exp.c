/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:17:27 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 00:09:38 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_ins(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (printf("bash: export: `%s': not a valid identifier\n", str), 1);
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=')
		return (printf("bash: export: `%s': not a valid identifier\n", str), 1);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '_')
				|| (str[i] == '+' && str[i + 1] == '=')))
		{
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		i++;
	}
	return (0);
}

char	**ins_exp(char *str, char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	return (new);
}

char	**process_valid_export(char *str, char **new_env)
{
	int		j;
	char	*tmp;
	char	**old_env;

	j = check_same(str, new_env);
	if (j != -1)
		return (handle_existing_var(str, new_env, j));
	else
	{
		tmp = ft_rmchar(str, '+');
		old_env = new_env;
		new_env = ins_exp(tmp, new_env);
		free_arr(old_env, NULL);
		free(tmp);
		return (new_env);
	}
}

char	**handle_existing_var(char *str, char **new_env, int j)
{
	char	*val;
	char	*tmp;

	if (ft_strchr(str, '+'))
	{
		val = ft_strchr(str, '=');
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
	else if (ft_strchr(str, '='))
	{
		free(new_env[j]);
		new_env[j] = ft_strdup(str);
	}
	return (new_env);
}

char	**add_exp(char **str, char **envp, int *es)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = dup_env(envp);
	if (!new_env)
		return (NULL);
	while (str[i])
	{
		if (check_ins(str[i]) == 0)
			new_env = process_valid_export(str[i], new_env);
		else
			*es = 1;
		i++;
	}
	return (new_env);
}
