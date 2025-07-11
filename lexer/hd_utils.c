/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:59:19 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 18:55:27 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_delim(t_shell *shell, t_token **tmp, t_cmd *cmd, int *es)
{
	t_token	*delim;
	char	*delimiter;

	delim = (*tmp)->next;
	if (delim)
	{
		delimiter = delim->value;
		handle_heredoc(shell, delimiter, cmd, es);
		*tmp = (*tmp)->next->next;
	}
}

int	validate_heredoc(char **input)
{
	if (*input && (*input)[0] == '<' && (*input)[1] == '<')
	{
		*input += 2;
		while (**input == ' ')
			(*input)++;
		if (**input == '\0')
			return (1);
		return (0);
	}
	return (0);
}

void	handle_heredoc(t_shell *shell, char *delimiter, t_cmd *cmd, int *es)
{
	int		hdoc_fd;
	char	*fd_str;

	hdoc_fd = heredoc_pipe(shell, delimiter, es);
	if (hdoc_fd < 0)
		return ;
	fd_str = ft_itoa(hdoc_fd);
	if (!fd_str)
	{
		close(hdoc_fd);
		return ;
	}
	add_redir(&cmd->redir, fd_str, HEREDOC);
	free(fd_str);
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_status = SIGINT;
		write(1, "\n", 1);
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		close(STDIN_FILENO);
	}
}
