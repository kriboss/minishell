/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 00:17:08 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	parsing(t_shell *shell, char **envp)
{
	if (validate_input(shell->input))
	{
		printf("bash: syntax error near unexpected token '%s'\n", shell->input);
		return ;
	}
	tokenize(shell);
	tok_cmd(shell, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	**str;

	if (ac != 1)
	{
		printf("Usage: %s\n", av[0]);
		return (1);
	}
	shell.tokens = NULL;
	shell.input = NULL;
	shell.cmds = NULL;
	shell.es = 0;
	shell.i = -1;
	str = dup_env(envp);
	start_signals();
	print_header();
	while (1)
	{
		
		ft_readline(&shell);
		if (!shell.input)
		{
			printf("exit\n");
			free_all(&shell);
			free_arr(str, NULL);
			str = NULL;
			break ;
		}
		parsing(&shell, str);
		if (!shell.cmds || !shell.cmds->argv || !shell.cmds->argv[0])
		{
			free_all(&shell);
			shell.input = NULL;
		}
		else
		{
			if (shell.cmds && shell.cmds->argv && shell.cmds->next)
				pipex(&shell, str);
			else
				str = execute(&shell, shell.cmds->argv, str, NULL);
			free_all(&shell);
			shell.input = NULL;
		}
	}
	rl_clear_history();
	free_all(&shell);
	free_arr(str, NULL);
	str = NULL;
	return (0);
}
