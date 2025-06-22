/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:38 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/18 13:21:14 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_word(char c)
{
    if (is_space(c) || is_special(c))
        return 0;
    return 1;
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\b' || c == '\n' || c == '\v') 
        return (1);
    return (0);
}

int is_special(char c)
{
    if (c == '<' || c == '>' || c == '|' ||
        c == '&' || c == '$' || c == '\'' || c == '\"')
        return (1);
    return (0);
}

void    tokenadd_back(t_token **lst, t_token *new)
{
    t_token *ptr;

    if (!new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    ptr = *lst;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = new;
}

void ft_readline(t_shell *shell)
{
    shell->input = readline("mininshell> ");
    if (!shell->input)
    {
        free_all(shell);
        exit(0);
    }
    if (shell->input[0])
        add_history(shell->input);
}

void init(t_cmd *cmd)
{
    cmd->argv = NULL;
    cmd->redir = NULL;
    cmd->next = NULL;
}
