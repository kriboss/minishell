/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/07 18:25:10 by sel-khao         ###   ########.fr       */
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

char	**add_word(char **argv, char *word)
{
	int		i;
	int		j;
	char	**av;

	i = 0;
	j = 0;
	if (argv)
	{
		while (argv[i])
			i++;
	}
	av = malloc(sizeof(char *) * (i + 2));
	if (!av)
		return (NULL);
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

void	parsing(t_shell *shell, char **envp)
{
	int		i;
	t_token	*token;
	t_cmd	*cmd;

	if (validate_input(shell->input))
	{
		printf("Invalid input: %s\n", shell->input);
		return ;
	}
	tokenize(shell);
	printf("Tokens:\n");
	token = shell->tokens;
	while (token)
	{
		printf("Token: '%s', Type: %d, Quote: %c\n", token->value, token->type, token->quote);
		printf("  type: %d, value: '%s'\n", token->type, token->value);
		token = token->next;
	}
	tok_cmd(shell, envp);
	cmd = shell->cmds;
	while (cmd)
	{
		printf("Command:\n");
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

/*void	parsing(t_shell *shell, char **envp)
{
	if (validate_input(shell->input))
	{
		printf("bash: syntax error near unexpected token '%s'\n", shell->input);
		return ;
	}
	tokenize(shell);
	tok_cmd(shell, envp);
}*/

int	heredoc_pipe(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
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
				str = execute(&shell, shell.cmds->argv, str);
			free_all(&shell);
			shell.input = NULL;
		}
	}
	free_all(&shell);
	free_arr(str, NULL);
	str = NULL;
	return (0);
}
