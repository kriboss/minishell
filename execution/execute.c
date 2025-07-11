/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/11 19:23:07 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

static char	**handle_builtins(t_shell *shell, char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		shell->es = cd(cmd + 1, envp);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		shell->es = pwd();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		shell->es = ft_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		shell->es = env(envp);
	else if (ft_strcmp(cmd[0], "export") == 0)
		envp = export(envp, cmd + 1, &shell->es);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		shell->es = unset(cmd + 1, envp);
	return (envp);
}

static char	**handle_exit_cmd(t_shell *shell, char **cmd, char **envp, t_fd f)
{
	restore_fds(f.input, f.output);
	rl_clear_history();
	shell->es = exitt(shell, envp, cmd + 1);
	return (envp);
}

char	**execute(t_shell *shell, char **cmd, char *envp[])
{
	t_fd	f;

	f.input = dup(STDIN_FILENO);
	f.output = dup(STDOUT_FILENO);
	if (handle_redirections(shell->cmds))
	{
		restore_fds(f.input, f.output);
		return (envp);
	}
	if (is_builtin(cmd[0]) == 1)
		shell->status = 0;
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (handle_exit_cmd(shell, cmd, envp, f));
	else if (is_builtin(cmd[0]))
		envp = handle_builtins(shell, cmd, envp);
	else
		shell->es = exec_external(shell, shell->cmds->argv, envp, &f);
	restore_fds(f.input, f.output);
	return (envp);
}

void	restore_fds(int in, int out)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
}
