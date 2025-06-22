/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/18 14:39:56 by sara             ###   ########.fr       */
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
# define SQUOTE		7
# define DQUOTE		8
# define VAR		9
# define INFILE		10
# define OUTFILE	11
# define APPEND		12
# define HDOC		13

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>       // access, fork, execve, chdir, getcwd, dup, dup2, pipe, isatty, ttyname, ttyslot, read, close
# include <fcntl.h>        // open, unlink
# include <string.h>       // strerror
# include <sys/types.h>    // wait, waitpid, wait3, wait4, stat-related types
# include <sys/wait.h>     // wait, waitpid, wait3, wait4
# include <sys/stat.h>     // stat, lstat, fstat
# include <signal.h>       // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>       // opendir, readdir, closedir
# include <termios.h>      // tcsetattr, tcgetattr
# include <termcap.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>       // for termcap on some systems
# include <sys/ioctl.h>    // ioctl
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

# define RESET   "\033[0m"
# define BLUE    "\033[34m"
# define CYAN    "\033[36m"
# define BOLD    "\033[1m"

typedef struct env_s
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_redir
{
	char	*filename;
	int		type;//infile or outfile
	struct	s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char			**argv;//for kri
	t_redir			*redir;
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

int		is_word(char c);
int		is_space(char c);
int		is_special(char c);
int		mult_redir(char *input);

int		validate_quote(char *str);
int		validate_pipe(char *input);
int		validate_input(char *input);
int		validate_redirection(char *input);
int		validate_redirection(char *input);

void	free_cmds(t_cmd *cmds);
void	free_tokens(t_token *tokens);
void	free_redir(t_redir *redir);
void	free_all(t_shell *shell);

void	init(t_cmd *cmd);
void	ft_readline(t_shell *shell);

void	parsing(t_shell *shell);
void	create_token(t_shell *shell, char *input, int *i);
void	tok_cmd(t_shell *shell);
char	**add_word(char **argv, char *word);
void	add_token(t_shell *shell, char *value, int type);
void    tokenadd_back(t_token **lst, t_token *new);
void	tokenize(t_shell *shell);
void	check_type(t_token **tmp, t_cmd *cmd);
void	check_type2(t_token **tmp, t_cmd **cmd);
void	add_redir(t_redir **redir_list, char *filename, int type);


int		exit_shell(int status,t_shell *shell, char **str);
int		print_exp(char **str);
int		check_same(char *str, char **envp);
int		unset(char **str, char **envp);
int		ft_strcmp(char *s1, const char *s2);
int		pipex(t_shell *shell, char **cmds, char **envp);

int handle_redirections(t_cmd *cmd);

int		exec_external(char **args, char **envp);
int		red_out(t_shell *shell, char **cmds, char **envp);
int		red_in(t_shell *shell);
int		red_app(t_shell *shell);

char	**add_exp(char **str, char **envp);
char	**dup_env(char **envp);
char	**execute(t_shell *shell, char **cmd, char *envp[]);
char	*ft_rmchar(char *str, char c);

void	free_arr(char **str, char **new);
void	start_signals(void);


#endif