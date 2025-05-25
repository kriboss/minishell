/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/25 20:09:02 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WORD       1
# define EOF        2
# define REDIRECT   3
# define PIPE       4
# define HEREDOC    5
# define DOLLAR		6
# define SEMICOLON	7
# define QUOTE		8
# define BG			9
# define VAR		10

# include <stdio.h>        // printf, perror
# include <stdlib.h>       // malloc, free, exit, getenv
# include <unistd.h>       // write, access, fork, execve, chdir, getcwd, dup, dup2, pipe, isatty, ttyname, ttyslot, read, close
# include <fcntl.h>        // open, unlink
# include <string.h>       // strerror
# include <sys/types.h>    // wait, waitpid, wait3, wait4, stat-related types
# include <sys/wait.h>     // wait, waitpid, wait3, wait4
# include <sys/stat.h>     // stat, lstat, fstat
# include <signal.h>       // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>       // opendir, readdir, closedir
# include <termios.h>      // tcsetattr, tcgetattr
# include <termcap.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>       // May be needed for termcap on some systems
# include <sys/ioctl.h>    // ioctl
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	int				append; 
	int				heredoc;
	char			**argv;//for kri
	char			*infile;
	char			*outfile;
	char			*delim;
	struct s_cmd	*next; 
}	t_cmd;

typedef struct s_token
{
	char			*value; 
	int				type; 
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

int		is_space(char c);
int		is_special(char c);
int		mult_redir(char *input);
int		validate_quote(char *str);
int		validate_pipe(char *input);
int		validate_input(char *input);
int		validate_redirection(char *input);
int		validate_redirection(char *input);

void free_cmds(t_cmd *cmds);
void free_tokens(t_token *tokens);
void	check_type(t_token **tmp, t_cmd *cmd);
void	init(t_cmd *cmd);
void	create_token(t_shell *shell, char *input, int *i);
void	tok_cmd(t_shell *shell);
char	**add_word(char **argv, char *word);
void	free_all(t_shell *shell);
void	something(t_shell *shell);
void	ft_readline(t_shell *shell);
void    tokenadd_back(t_token **lst, t_token *new);
void	add_token(t_shell *shell, char *value, int type);

#endif