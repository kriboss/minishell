#include "minishell.h"

void free_all(t_shell *shell)
{
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    if (shell->tokens)
    {
        free_tokens(shell->tokens);
        shell->tokens = NULL;
    }
    if (shell->cmds)
    {
        free_cmds(shell->cmds);
        shell->cmds = NULL;
    }
    clear_history();
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_cmds(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;

    while (cmds)
    {
        tmp = cmds;
        cmds = cmds->next;
        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
            {
                free(tmp->argv[i]);
                i++;
            }
            free(tmp->argv);
        }
        if (tmp->infile)
            free(tmp->infile);
        if (tmp->outfile)
            free(tmp->outfile);
        if (tmp->delim)
            free(tmp->delim);
        free(tmp);
    }
}
