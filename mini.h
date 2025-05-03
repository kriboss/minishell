/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:23:15 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/03 12:19:16 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MININSHELL_H
# define MINISHELL_H

# define TOK_CMD		1   //
# define TOK_ARG		2   // "-l", "/home/user"
# define TOK_REDIRECT	3  // Redirect operator ">", "<", ">>"
# define TOK_PIPE		4   //  "|"
# define TOK_HEREDOC	5   // "<<"

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

typedef struct s_cmd
{
	char			**argv; //args for execve
	char			*infile; // input fle for <
	char			*outfile; // outputfile for > >>
	int				append; // 1 if >> (append), 0 if > (truncate)
	int				heredoc;
	char			*delim;
	struct s_cmd	*next; //next cmd in a pipeline
} t_cmd;

typedef struct s_token
{
	char			*value; //value of the token
	int				type; //what type of token it is: arg, cmd, oper
	struct s_token	*next; //pointer to next token
} t_token;

char	quoted(char *line, int *i);
/*
argv			Needed by execve(). Contains command + args like ls -la.
infile			If user uses < input.txt, store "input.txt" here. Used in open() and dup2().
outfile			If user uses > output.txt or >>, store filename here.
append			To distinguish between > and >>. You’ll set this to 1 for >>.
heredoc			Set to 1 if user wrote <<. Needed so your partner knows to read from a temp file.
heredoc_delim	What the user typed after <<. Used to know when to stop reading input.
next			So you can link multiple commands like in `ls
*/

#endif