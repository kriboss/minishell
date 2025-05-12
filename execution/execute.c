/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/12 12:53:19 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char *path)
{
	if (!path || !*path)
	{
		if (chdir(getenv("HOME")) == -1)
			return (1);
		return (0);
	}
	while (*path == ' ')
		path++;
	if (chdir(path) == -1)
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

	if (str == NULL)
		return (printf("\n"), 0);
	while (*str == ' ')
		str++;
	i = 0;
	flag = 0;
	if (str[i] == '-' && str[i + 1] == 'n'
		&& (str[i + 2] == ' ' || str[i + 2] == '\0'))
	{
		flag = 1;
		i += 2;
		while (str[i] == ' ')
			i++;
	}
	if (flag == 0)
		printf("%s\n", str);
	else
		printf("%s", &str[i]);
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
	{
		print_exp(env);
	}
	else
	{
		return (add_exp(str + 1, env));
	}
	return (env);
}

int	exit_shell(int status, char **str)
{
	printf("Exiting shell...\n");
	if (str != NULL)
	{
		free_all(str, NULL);
		status = 0;
	}
	clear_history();
	exit(status);
}

char	**execute(char *cmd, char *envp[])
{
	char	es;
	char	**cmds;

	es = 0;
	if (ft_strchr(cmd, '|'))
	{
		cmds = ft_split(cmd, '|');
		if (cmds == NULL)
			return (NULL);
		es = pipex(cmds, envp);
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		es = cd(ft_strchr(cmd, ' '));
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		es = pwd();
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		es = echo(ft_strchr(cmd, ' '));
	else if (ft_strncmp(cmd, "env", 3) == 0)
		es = env(envp);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		envp = export(envp, ft_strchr(cmd, ' '));
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		es = unset(envp, ft_strchr(cmd, ' '));
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		exit_shell(es, envp);
	else
		es = exec_external(ft_split(cmd, ' '), envp);
	return (envp);
}
