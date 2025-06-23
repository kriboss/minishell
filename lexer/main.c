/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/23 13:09:06 by sel-khao         ###   ########.fr       */
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

char	**add_word(char **argv, char *word)
{
	int i = 0;
	int j = 0;
	char **av;

	if (argv)
	{
		while (argv[i])
			i++;
	}
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
	t_token *prev;

	tmp = shell->tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	init(cmd);
	shell->cmds = cmd;
	while (tmp)
	{
		prev = tmp;
		if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd, shell);
		if (tmp == prev)
			tmp = tmp->next;
	}
}

void parsing(t_shell *shell)
{
    if (validate_input(shell->input))
    {
        printf("Invalid input: %s\n", shell->input);
        return;
    }
    tokenize(shell);
    tok_cmd(shell);
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
        parsing(&shell);
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
