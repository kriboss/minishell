/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:49:05 by kbossio           #+#    #+#             */
/*   Updated: 2025/05/06 11:55:25 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

typedef struct env_s
{
	char	*key;
	char	*value;
}	t_env;

int		print_exp(char **str);
char	**ins_exp(char *str, char **envp);
int		unset(char **envp, char *str);
int		ft_strcmp(char *s1, const char *s2);
char	**dup_env(char **envp);
void	free_all(char **str, char **new);
int		check_same(char *str, char **envp);
int		execute(char *cmd, char *envp[]);
void		start_signals(void);

#endif

