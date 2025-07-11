/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:29:31 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 12:51:18 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **path, char **envp)
{
	char	*dir;

	if (!path || !path[0])
	{
		dir = find_env(envp, "HOME");
		if (!dir)
			return (printf("bash: cd: HOME not set\n"), 1);
		if (chdir(dir) == -1)
			return (printf("bash: cd: %s: No such file or dir\n", dir), 1);
		return (0);
	}
	if (path[1])
		return (printf("bash: cd: too many arguments\n"), 1);
	dir = path[0];
	while (*dir == ' ')
		dir++;
	if (chdir(dir) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", dir);
		return (1);
	}
	return (0);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		return (free(pwd), 0);
	}
	else
	{
		perror("pwd");
		return (free(pwd), 1);
	}
}

int	ft_echo(char **str)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (str == NULL || *str == NULL)
	{
		printf("\n");
		return (0);
	}
	if (str[0] && str[0][0] == '-' && str[0][1] == 'n' && str[0][2] == '\0')
	{
		n_flag = 1;
		i = 1;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

int	env(char **envp)
{
	int		i;
	int		j;
	char	**order;

	order = order_env(envp);
	i = 0;
	while (order[i] != NULL)
	{
		j = 0;
		while (order[i][j] != '=' && order[i][j] != '\0')
			j++;
		if (order[i][j] == '=')
			printf("%s\n", order[i]);
		i++;
	}
	free_matrix(order);
	return (0);
}

char	**export(char **env, char **str, int *es)
{
	char	**tmp;

	if (str == NULL || *str == NULL)
	{
		print_exp(env);
		*es = 0;
	}
	else
	{
		tmp = env;
		env = add_exp(str, env, es);
		free_arr(tmp, NULL);
	}
	return (env);
}
