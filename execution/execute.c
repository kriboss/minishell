/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/07 18:49:05 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//8
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
	char	**tmp;

	if (str == NULL || *str == NULL)
		print_exp(env);
	else
	{
		tmp = env;
		env = add_exp(str, env);	
		free_arr(tmp, NULL);
	}
	return (env);
}

int	check_overflow(char *str, long long *result)
{
	int	i;
	int	sign;
	unsigned long long	num;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if ((num > LLONG_MAX && sign == 1) || (num > LLONG_MIN && sign == -1))
			return (0);
		i++;
	}
	*result = (long long)num * sign;
	return (1);
}

int	exit_shell(int status, t_shell *shell, char **envp, char **str)
{
	long long	status_code;
	int			fd;

	fd = 0;
	if (str && str[0])
	{
	    if (str[1])
			return (write(2, "bash: exit: too many arguments\n", 31), 1);
		printf("exit\n");
		if (check_overflow(str[0], &status_code) == 0)
		{
			write(2, "bash: exit: ", 12);
			write(2, str[0], ft_strlen(str[0]));
			write(2, ": numeric argument required\n", 28);
			status_code = 2;
		}
		else
			status_code = status_code % 256;
		if (envp)
		free_arr(envp, NULL);
		clear_history();
		if (shell)
			free_all(shell);
		while (fd < 1024)
		{
			close(fd);
			fd++;
		}
		exit(status_code);
	}
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
	if (ft_strcmp(cmd[0], "cd") == 0)
		es = cd(cmd + 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		es = pwd();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		es = ft_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		es = env(envp);
	else if (ft_strcmp(cmd[0], "export") == 0)
		envp = export(envp, cmd + 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		es = unset(cmd + 1, envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		exit_shell(es, shell, envp, cmd + 1);
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