#include "minishell.h"

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\b' || c == '\n' || c == '\v') 
        return (1);
    return (0);
}

int is_special(char c)
{
    if (c == '<' || c == '>' || c == ';' || c == '|' ||
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
    cmd->append = 0;
    cmd->heredoc = 0;
    cmd->argv = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->delim = NULL;
    cmd->next = NULL;
}
