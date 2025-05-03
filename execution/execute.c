/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/03 12:04:29 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 1024);
	if (getcwd(pwd, sizeof(pwd)) != NULL)
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
			flag = 1;
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
			printf("%s", str);
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

int	export(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL)
		print_exp(env);
	return (1);
}

int	exit_shell(void)
{
	printf("Exiting shell...\n");
	exit(0);
}
/*
int	execute_command(char *command)
{
	if (strcmp(command, "cd") == 0)
		return (cd("/home"));
	else if (strcmp(command, "pwd") == 0)
		return (pwd());
	else if (strcmp(command, "echo") == 0)
		return (echo("Hello World!"));
	else if (strcmp(command, "env") == 0)
		return (env("ciao"));
	else if (strcmp(command, "exit") == 0)
		return (exit_shell());
	else
	{
		printf("Command not found: %s\n", command);
		return (1);
	}
}
*/

int	main(int argc, char *argv[], char *envp[])
{

	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return (1);
	}
	export(NULL, envp);
	return (0);
}
