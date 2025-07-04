/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/04 18:45:20 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **path)
{
	char	*dir;

	if (!path || !path[0])
	{
		dir = getenv("HOME");
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
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
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
		print_exp(env);
	else
		return (add_exp(str, env));
	return (env);
}

int	exit_shell(int status, t_shell *shell, char **str)
{
	printf("Exiting shell...\n");
	if (str != NULL)
		free_arr(str, NULL);
	if (shell && shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	clear_history();
	exit(status);
}

char	**execute(t_shell *shell, char **cmd, char *envp[])
{
	int		stdout_backup;
	int		stdin_backup;
	char	es;

	es = 0;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (handle_redirections(shell->cmds))
	{
		restore_fds(stdin_backup, stdout_backup);
		return (envp);
	}
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		es = cd(cmd + 1);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		es = pwd();
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		es = ft_echo(cmd + 1);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		es = env(envp);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		envp = export(envp, cmd + 1);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		es = unset(cmd + 1, envp);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		exit_shell(es, shell, envp);
	}
	else
		es = exec_external(shell->cmds, shell->cmds->argv, envp);
	restore_fds(stdin_backup, stdout_backup);
	return (envp);
}

void	restore_fds(int in, int out)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
}