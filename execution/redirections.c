/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:15:41 by kbossio           #+#    #+#             */
/*   Updated: 2025/06/18 20:32:02 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int red_out(t_shell *shell, char **cmds, char **envp)
{
    t_redir *redir = shell->cmds->redir;
    int fd;
    int last_fd = -1;
    while (redir)
    {
        if (redir->type == OUTFILE)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("Error opening output file");
                return 1;
            }
            if (last_fd != -1)
                close(last_fd);  // Close previous fd if any (only last redir matters)
            last_fd = fd;
        }
        else if (redir->type == APPEND)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("Error opening append file");
                return 1;
            }
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd;
        }
        redir = redir->next;
    }
    if (last_fd != -1)
        dup2(last_fd, STDOUT_FILENO);
    execute(shell, cmds, envp);
    if (last_fd != -1)
        close(last_fd);
    return 0;
}

int red_in(t_shell *shell)
{
    t_redir *redir = shell->cmds->redir;
    int fd;
    int last_fd = -1;

    while (redir)
    {
        if (redir->type == INFILE)
        {
            fd = open(redir->filename, O_RDONLY);
            if (fd == -1)
            {
                perror("Error opening input file");
                return 1;
            }
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd;
        }
        redir = redir->next;
    }
    if (last_fd != -1)
        dup2(last_fd, STDIN_FILENO);
    if (last_fd != -1)
        close(last_fd);
    return 0;
}

int red_app(t_shell *shell)
{
    t_redir *redir = shell->cmds->redir;
    int fd;
    int last_fd = -1;

    while (redir)
    {
        if (redir->type == APPEND)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("Error opening append file");
                return 1;
            }
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd;
        }
        redir = redir->next;
    }
    if (last_fd != -1)
        dup2(last_fd, STDOUT_FILENO);
    if (last_fd != -1)
        close(last_fd);
    return 0;
}

int handle_redirections(t_cmd *cmd)
{
    t_redir *redir = cmd->redir;
    int fd;

    while (redir)
    {
        if (redir->type == OUTFILE)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (perror("open"), 1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == APPEND)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (perror("open"), 1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == INFILE)
        {
            fd = open(redir->filename, O_RDONLY);
            if (fd == -1)
                return (perror("open"), 1);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redir = redir->next;
    }
    return 0;
}
