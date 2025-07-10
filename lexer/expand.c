/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:42:41 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 10:42:44 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_exit_status(t_expand *exp)
{
	char	*itoa_res;

	if (g_status != 0)
		itoa_res = ft_itoa(g_status);
	else
		itoa_res = ft_itoa(exp->es[0]);
	*(exp->res) = str_append(*(exp)->res, itoa_res);
	free(itoa_res);
	(*(exp->i))++;
	return (*(exp)->res);
}

static char	*extract_var_key(const char *input, int start, int end)
{
	return (ft_substr(input, start, end - start));
}

static char	*handle_var_exp(t_expand *exp)
{
	int		start;
	char	*key;
	char	*val;

	start = *(exp->i);
	while (ft_isalnum(exp->input[*(exp->i)]) || exp->input[*(exp->i)] == '_')
		(*(exp->i))++;
	key = extract_var_key(exp->input, start, *(exp->i));
	val = env_value(exp->envp, key);
	if (!val)
		val = "";
	*(exp->res) = str_append(*(exp->res), val);
	free(key);
	return (*(exp->res));
}

static char	*process_dollar_sign(t_expand *exp)
{
	(*(exp->i))++;
	if (exp->input[*(exp->i)] == '\0')
	{
		*(exp->res) = append_char(*(exp->res), '$');
		return (*(exp->res));
	}
	else if (exp->input[*(exp->i)] == '?')
		return (handle_exit_status(exp));
	else if (ft_isalpha(exp->input[*(exp->i)]) || exp->input[*(exp->i)] == '_')
		return (handle_var_exp(exp));
	else
	{
		*(exp->res) = append_char(*(exp->res), '$');
		return (*(exp->res));
	}
}

char	*expand_var(const char *input, char **envp, int *es)
{
	int			i;
	char		*res;
	t_expand	exp;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	exp.res = &res;
	exp.input = input;
	exp.envp = envp;
	exp.es = es;
	exp.i = &i;
	while (input[i])
	{
		if (input[i] == '$')
			res = process_dollar_sign(&exp);
		else
			res = append_char(res, input[i++]);
	}
	return (res);
}
