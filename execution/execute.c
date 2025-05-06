/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/06 12:59:41 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char *path)
{
	if (!path)
	{
		if (chdir(getenv("HOME")) == -1)
			return (1);
	}
	else if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
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
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	echo(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ')
		{
			flag = 1;
			i += 3;
			break;
		}
		i++;
	}
	if (str == NULL)
	{
		if (flag == 0)
			printf("\n");
	}
	else
	{
		if (flag == 0)
				printf("%s\n", str);
		else
			printf("%s", &str[i]);
	}
	return (0);
}

int	env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		if (envp[i][j] == '=')
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

char	**export(char **env, char *str)
{
	if (str == NULL)
		print_exp(env);
	else
	{	
		return (ins_exp(str + 1, env));
	}
	return (NULL);
}

int	exit_shell(int status)
{
	printf("Exiting shell...\n");
	exit(status);
}

int	execute(char *cmd, char *envp[])
{
	char **str;
	char es;
	
	str = dup_env(envp);
	es = 0;
	export(str, NULL);
	printf("----------------------------------------\n----------------------------------------\n----------------------------------------\n----------------------------------------\n");
	export(str, "export");
	printf("----------------------------------------\n----------------------------------------\n----------------------------------------\n----------------------------------------\n");
	export(str, NULL);
	(void)cmd;
	/*
	if (ft_strncmp(cmd, "cd", 2) == 0)
		es = cd(ft_strchr(cmd, ' ') + 1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		es = pwd();
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		es = echo(ft_strchr(cmd, ' ') + 1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		es = env(str);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		export(str, ft_strchr(cmd, ' '));
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		es = unset(str, ft_strchr(cmd, ' ') + 1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		exit_shell(es);
	else
	{
		printf("Command not found: %s\n", cmd);
	}
	*/
	free_all(str, NULL);
	return (0);
}
