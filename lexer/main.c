/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 00:30:55 by sel-khao         ###   ########.fr       */
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

static char	**ft_minishell(t_shell *shell, char **str)
{
	ft_readline(shell);
	if (!shell->input)
	{
		printf("exit\n");
		free_all(shell);
		free_arr(str, NULL);
		return (str = NULL, NULL);
	}
	parsing(shell, str);
	count_pipe(shell);
	if (!shell->cmds || !shell->cmds->argv || !shell->cmds->argv[0])
	{
		free_all(shell);
		shell->input = NULL;
	}
	else
	{
		if (shell->cmds && shell->cmds->argv && shell->cmds->next)
			pipex(shell, str);
		else
			str = execute(shell, shell->cmds->argv, str);
		free_all(shell);
		shell->input = NULL;
	}
	return (str);
}

char	**initialize_shell(t_shell *shell, char **envp)
{
	shell->tokens = NULL;
	shell->input = NULL;
	shell->cmds = NULL;
	shell->pipe = 0;
	shell->es = 0;
	shell->i = -1;
	start_signals();
	print_header();
	return (dup_env(envp));
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
	str = initialize_shell(&shell, envp);
	while (1)
	{
		str = ft_minishell(&shell, str);
		if (!str)
			break ;
	}
	rl_clear_history();
	free_all(&shell);
	free_arr(str, NULL);
	str = NULL;
	return (0);
}
