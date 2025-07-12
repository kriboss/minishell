/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:36:51 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/12 12:39:48 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_status_code(t_shell *shell)
{
	if (g_status == INT_MIN)
		return ;
	if (g_status == SIGINT)
		shell->status = 130;
	if (g_status == SIGQUIT)
		shell->status = 131;
	g_status = INT_MIN;
}

int	init_heredoc(t_shell *shell, t_hd *hd, const char *delimiter, int *es)
{
	hd->delimiter = delimiter;
	hd->envp = shell->envp;
	hd->es = es;
	if (pipe(hd->pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	hd->stdin_backup = dup(STDIN_FILENO);
	shell->status = 0;
	signal(SIGINT, heredoc_sig);
	return (0);
}
