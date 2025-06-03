/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/25 20:07:06 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char **add_word(char **argv, char *word)
{
    int i = 0;
    int j = 0;
    char **av;
    
    while (argv && argv[i])
        i++;
    av = malloc(sizeof(char *) * (i + 2));
    if (!av)
        return NULL;
    while (j < i)
    {
        av[j] = argv[j];
        j++;
    }
    av[i] = ft_strdup(word);
    av[i + 1] = NULL;
    free(argv);
    return (av);
}

void tok_cmd(t_shell *shell)
{
    t_cmd *cmd;
    t_token *tmp;

    tmp = shell->tokens;
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return ;
    init(cmd);
    shell->cmds = cmd;
    while (tmp)
        check_type(&tmp, cmd);
}

void check_type(t_token **tmp, t_cmd *cmd)
{
    if ((*tmp)->type == WORD || (*tmp)->type == EOF)
    {
        cmd->argv = add_word(cmd->argv, (*tmp)->value);
        *tmp = (*tmp)->next;
    }
    else if ((*tmp)->type == REDIRECT && (*tmp)->next)
    {
        if (ft_strcmp((*tmp)->value, "<") == 0)
            cmd->infile = ft_strdup((*tmp)->next->value);
        else if (ft_strcmp((*tmp)->value, ">") == 0)
            cmd->outfile = ft_strdup((*tmp)->next->value);
        else if (ft_strcmp((*tmp)->value, ">>") == 0)
        {
            cmd->outfile = ft_strdup((*tmp)->next->value);
            cmd->append = 1;
        }
        *tmp = (*tmp)->next->next;
    }
    else if ((*tmp)->type == HEREDOC && (*tmp)->next)
    {
        cmd->delim = ft_strdup((*tmp)->next->value);
        cmd->heredoc = 1;
        *tmp = (*tmp)->next->next;
    }
}

void something(t_shell *shell)
{
    if (validate_input(shell->input))
    {
        printf("Invalid input: %s\n", shell->input);
        return ;
    }
    tokenize(shell);
    tok_cmd(shell);
    printf("Parsed commands from input: %s\n", shell->input);
}


int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_shell shell;

    shell.tokens = NULL;
    shell.input = NULL;
    shell.cmds = NULL;
    while (1)
    {
        ft_readline(&shell);
        if (!shell.input)
            free_all(&shell);
        something(&shell);
        shell.tokens = NULL;
        shell.cmds = NULL;
        free(shell.input);
        shell.input = NULL;
    }
    return 0;
}
