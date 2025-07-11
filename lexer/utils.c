/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:38 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 23:49:41 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_readline(t_shell *shell)
{
	shell->input = readline("mininshell> ");
	update_status_code(shell);
	if (!shell->input)
		return ;
	if (shell->input[0])
		add_history(shell->input);
}

void	init(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
}

void	signla_status(t_shell *shell, int *ok, int n)
{
	int	i;
	int	status;

	status = 0;
	*(ok) = 0;
	i = 0;
	while (i < n)
	{
		waitpid(shell->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == 130)
			*(ok) = 130;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 131)
			*(ok) = 131;
		if (WIFEXITED(status))
			shell->es = WEXITSTATUS(status);
		i++;
	}
}
