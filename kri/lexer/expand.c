
#include "../include/minishell.h"
//6
char	*str_append(char *base, const char *to_add)//concateno
{
	char	*str;
	size_t	base_len;
	size_t	add_len;

	if (!base)
		base = ft_strdup("");
	if (!to_add)
		to_add = "";
	base_len = ft_strlen(base);
	add_len = ft_strlen(to_add);
	str = malloc(base_len + add_len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, base, base_len + 1);
	ft_strlcat(str, to_add, base_len + add_len + 1);
	free(base);
	return (str);
}

char	*append_char(char *base, char c)
{
	size_t	len;
	char	*new_str;

	if (!base)
		base = ft_strdup("");
	len = ft_strlen(base);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, base, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(base);
	return (new_str);
}

char	*env_value(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!key || !envp)
	{
		write(1, "env error\n", 10);
		return (NULL);
	}
	i = match_word(key, envp);
	if (i != -1)
	{
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		if (envp[i][j] == '=')
			return (envp[i] + j + 1);
	}
	return (NULL);
}

void	check_type(t_token **tmp, t_cmd *cmd, char **envp)
{
	char	*expand;

	if ((*tmp)->type == WORD || (*tmp)->type == EOF)
	{
		if ((*tmp)->quote != '\'')
			expand = expand_var((*tmp)->value, envp);
		else
			expand = ft_strdup((*tmp)->value);
		if (!expand)
			expand = ft_strdup("");
		cmd->argv = add_word(cmd->argv, expand);
		free(expand);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->type == REDIRECT && (*tmp)->next)
		check_redi(cmd, tmp);
	else if ((*tmp)->type == HEREDOC && (*tmp)->next)
	{
		add_redir(&cmd->redir, (*tmp)->next->value, HEREDOC);
		*tmp = (*tmp)->next->next;
	}
	else
		*tmp = (*tmp)->next;
}

void	check_redi(t_cmd *cmd, t_token **tmp)
{
	if (ft_strcmp((*tmp)->value, "<") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, INFILE);
	else if (ft_strcmp((*tmp)->value, ">") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, OUTFILE);
	else if (ft_strcmp((*tmp)->value, ">>") == 0)
		add_redir(&cmd->redir, (*tmp)->next->value, APPEND);
	*tmp = (*tmp)->next->next;
}

char	*expand_var(const char *input, char **envp)
{
	int		i;
	int		start;
	char	*key;
	char	*val;
	char	*res;
	char	*itoa_res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '\0')
			{
				res = append_char(res, '$');
				break ;
			}
			else if (input[i] == '?')
			{
				itoa_res = ft_itoa(g_status);
				res = str_append(res, itoa_res);
				free(itoa_res);
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == '_')
			{
				start = i;
				while (ft_isalnum(input[i]) || input[i] == '_')
					i++;
				key = ft_substr(input, start, i - start);
				val = env_value(envp, key);
				if (!val)
					val = "";
				res = str_append(res, val);
				free(key);
			}
			else
				res = append_char(res, '$');
		}
		else
			res = append_char(res, input[i++]);
	}
	return (res);
}