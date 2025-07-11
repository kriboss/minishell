/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:13:11 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 10:13:15 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_delim(t_token **tmp, char **envp, t_cmd *cmd, int *es)
{
	t_token	*delim;
	char	*delimiter;

	delim = (*tmp)->next;
	if (delim)
	{
		delimiter = delim->value;
		handle_heredoc(delimiter, envp, cmd, es);
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

void	handle_heredoc(char *delimiter, char **envp, t_cmd *cmd, int *es)
{
	int		hdoc_fd;
	char	*fd_str;

	hdoc_fd = heredoc_pipe(delimiter, envp, es);
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
		g_status = 130;
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\n", 1);
	}
}

int	heredoc_pipe(const char *delimiter, char **envp, int *es)
{
	int		pipefd[2];
	char	*line;
	char	*expand;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		line = readline("> ");
		if (g_status == 130)
		{
			rl_done = 1;
			close(pipefd[1]);
			close(pipefd[0]);
			free(line);
			signal(SIGINT, signal_handler);
			return (-1);
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expand = expand_var(line, envp, es);
		if (!expand)
		{
			free(line);
			close(pipefd[1]);
			close(pipefd[0]);
			return (-1);
		}
		write(pipefd[1], expand, ft_strlen(expand));
		write(pipefd[1], "\n", 1);
		free(line);
		free(expand);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
