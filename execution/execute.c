/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/13 12:38:38 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **path)
{
	char *dir;

	if (!path || !path[0])
	{
		dir = getenv("HOME");
		if (!dir)
			return (printf("bash: cd: HOME not set\n"), 1);
		if (chdir(dir) == -1)
			return (printf("bash: cd: %s: No such file or directory\n", dir), 1);
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
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	echo(char **str)
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

char	**export(char **env, char **str)
{
	if (str == NULL || *str == NULL)
	{
		print_exp(env);
	}
	else
	{
		return (add_exp(str, env));
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
	if (ft_strrchr(cmd, '|'))
	{
		cmds = ft_split(cmd, '|');
		if (cmds == NULL)
			return (NULL);
		es = pipex(cmds, envp);
	}
	else if (ft_strrchr(cmd, '>') || ft_strrchr(cmd, '<'))
		es = handle_red(ft_split(cmd, ' '), envp);
	else
	{
		cmds = ft_split(cmd, ' ');
		if (ft_strncmp(cmd, "cd", 2) == 0)
			es = cd(cmds + 1);
		else if (ft_strncmp(cmd, "pwd", 3) == 0)
			es = pwd();
		else if (ft_strncmp(cmd, "echo", 4) == 0)
			es = echo(cmds + 1);
		else if (ft_strncmp(cmd, "env", 3) == 0)
			es = env(envp);
		else if (ft_strncmp(cmd, "export", 6) == 0)
			envp = export(envp, cmds + 1);
		else if (ft_strncmp(cmd, "unset", 5) == 0)
			es = unset(cmds + 1, envp);
		else if (ft_strncmp(cmd, "exit", 4) == 0)
			exit_shell(es, envp);
		else
			es = exec_external(cmds, envp);
		free_all(cmds, NULL);
	}
	return (envp);
}
