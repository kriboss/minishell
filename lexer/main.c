/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/26 14:18:43 by sel-khao         ###   ########.fr       */
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

/* void	parsing(t_shell *shell)
{
	int		i;
	t_token	*token;
	t_cmd	*cmd;

	if (validate_input(shell->input))
	{
		printf("Invalid input: %s\n", shell->input);
		return ;
	}
	//printf("2\n");
	tokenize(shell);
	//printf("3\n");
	printf("Tokens:\n");
	token = shell->tokens;
	while (token)
	{
		printf("  type: %d, value: '%s'\n", token->type, token->value);
		token = token->next;
	}
	tok_cmd(shell);
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
} */

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
			break;
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
			break ;
		parsing(&shell);
		if (shell.cmds && shell.cmds->argv)
			str = execute(&shell, shell.cmds->argv, str);
		else
			ft_putendl_fd("No command to execute", STDERR_FILENO);
		free_all(&shell);
		shell.input = NULL;
	}
	return (0);
}

/*LEAKS:
==417900== 5 bytes in 1 blocks are still reachable in loss record 2 of 67
==417900==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==417900==    by 0x405474: ft_strdup (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x401B81: add_word (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x4020AA: check_type (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x40192A: tok_cmd (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x401C1F: parsing (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x401DB8: main (in /home/sel-khao/Desktop/minishell.git/minishell)

==417900== 24 bytes in 1 blocks are still reachable in loss record 15 of 67
==417900==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==417900==    by 0x4018C1: tok_cmd (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x401C1F: parsing (in /home/sel-khao/Desktop/minishell.git/minishell)
==417900==    by 0x401DB8: main (in /home/sel-khao/Desktop/minishell.git/minishell)


*/
