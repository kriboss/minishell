/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/06/18 15:06:57 by sara             ###   ########.fr       */
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

int	exit_shell(int status,t_shell *shell, char **str)
{
	printf("Exiting shell...\n");
	if (str != NULL)
	{
		free_arr(str, NULL);
		status = 0;
	}
	if (shell && shell->tokens)
    {
        free_tokens(shell->tokens);
        shell->tokens = NULL;
    }
	clear_history();
	exit(status);
}

int check_cmd(t_shell *shell, char **cmds, char **envp)
{
    int i = 0;
    (void)envp;
    while (cmds[i])
    {
        if (ft_strncmp(cmds[i], "|", 1) == 0)
            printf("Found pipe symbol '|', skipping pipex for now\n");
        else if (ft_strncmp(cmds[i], ">>", 2) == 0)
            printf("Found '>>', skipping red_app for now\n");
        else if (ft_strncmp(cmds[i], ">", 1) == 0)
		{
			printf("Found '>', skipping red_out for now\n");
			red_out(shell, cmds, envp);
        }
        else if (ft_strncmp(cmds[i], "<", 1) == 0)
            printf("Found '<', skipping red_in for now\n");
        i++;
    }
    return (-2);
}

char **execute(t_shell *shell, char **cmd, char *envp[])
{
	int		stdout_backup = dup(STDOUT_FILENO);
	int		stdin_backup = dup(STDIN_FILENO);
	char	es = 0;

	if (handle_redirections(shell->cmds))
		return (envp);
	if (check_cmd(shell, cmd, envp) == -2)
	{
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
			exit_shell(es, shell, envp);
		else
			es = exec_external(cmd, envp);
	}
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdout_backup);
	close(stdin_backup);
	return (envp);
}


