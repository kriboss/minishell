/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:45:31 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/11 19:07:19 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_overflow(char *str, long long *result)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if (((long long)num > LLONG_MAX && sign == 1)
			|| ((long long)num > LLONG_MIN && sign == -1))
			return (0);
		i++;
	}
	*result = (long long)num * sign;
	return (1);
}

void	cleanup_and_exit(t_shell *shell, char **envp, long long status_code)
{
	int	fd;

	(void)shell;
	if (envp)
		free_arr(envp, NULL);
	rl_clear_history();
	if (shell)
		free_all(shell);
	fd = 0;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(status_code);
}

int	exitt(t_shell *shell, char **envp, char **str)
{
	long long	status_code;

	status_code = shell->es;
	if (str && str[0])
	{
		printf("exit\n");
		if (str[1])
			return (write(2, "bash: exit: too many arguments\n", 31), 1);
		if (check_overflow(str[0], &status_code) == 0)
		{
			write(2, "bash: exit: ", 12);
			write(2, str[0], ft_strlen(str[0]));
			write(2, ": numeric argument required\n", 28);
			status_code = 2;
		}
		else
			status_code = status_code % 256;
	}
	cleanup_and_exit(shell, envp, status_code);
	return (0);
}
