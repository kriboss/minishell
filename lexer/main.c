/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/16 11:09:25 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	print_header(void)
{
	printf(BOLD CYAN);
	printf(" __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n");
	printf("|  \\/  |_   _| \\ | |_   _|/ ____| |  | |  ____| |    | |     \n");
	printf("| \\  / | | | |  \\| | | | | (___ | |__| | |__  | |    | |     \n");
	printf("| |\\/| | | | | . ` | | |  \\___ \\|  __  |  __| | |    | |     ");
	printf("\n");
	printf("| |  | |_| |_| |\\  |_| |_ ____) | |  | | |____| |____| |____ \n");
	printf("|_|  |_|_____|_| \\_|_____|_____/|_|  |_|______|______|______|\n");
	printf("                                                             \n");
	printf("                                                             \n");
	printf(RESET);
}

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
    printf("valid input: %s\n", shell->input);
}


int main(int ac, char **av, char **envp)
{
    t_shell shell;
    char	**str;

	if (ac != 1)
	{
		printf("Usage: %s\n", av[0]);
		return (1);
	}
    shell.tokens = NULL;
    shell.input = NULL;
    shell.cmds = NULL;
    str = dup_env(envp);
	start_signals();
	print_header();
    while (1)
    {
        ft_readline(&shell);
        if (!shell.input)
            free_all(&shell);
        something(&shell);
        if (shell.cmds && shell.cmds->argv)
	        str = execute(&shell, shell.cmds->argv, str);
        else
	        ft_putendl_fd("No command to execute", STDERR_FILENO);
        shell.tokens = NULL;
        shell.cmds = NULL;
        free(shell.input);
        shell.input = NULL;
    }
    return 0;
}
