/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:38 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 19:37:48 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_word(char c)
{
	int	result;

	result = !(is_space(c) || is_special(c));
	return (result);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\b' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

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
