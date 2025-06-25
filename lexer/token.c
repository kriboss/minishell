/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/06/25 14:46:14 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize(t_shell *shell)
{
	int		i;
	char	*input;
	int		start;

	i = 0;
	input = shell->input;
	while (input[i] && is_space(input[i]))
		i++;
	while(input[i])
	{
		if (is_special(input[i]))
			create_token(shell, input, &i);
		else if (is_word(input[i]))
		{
			start = i;
			while (input[i] && is_word(input[i]))
				i++;
			char *word = ft_substr(input, start, i - start);
			add_token(shell, word, WORD);
			free(word);
		}
		while (input[i] && is_space(input[i]))
			i++;
	}
}

void	add_token(t_shell *shell, char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	if (!shell->tokens)
	{
		shell->tokens = new_token;
		return ;
	}
	else
		tokenadd_back(&shell->tokens, new_token);
}

/* void mult_word(t_token **head)
{
	t_token *curr;
	char *word;

	if (!head || !(*head))
		return ;
	curr = *head;
	while (curr != NULL && curr->next != NULL)
	{
    	if (curr->type == WORD && curr->next->type == WORD)
    	{
    	    word = ft_strjoin(curr->value, curr->next->value);
    	    if (!word)
				return ;
			free(curr->value);
    	    curr->value = word;
    	}
    	else
        	curr = curr->next;
	}
} */

void	tok_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*tmp;
	t_token	*prev;

	tmp = shell->tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	init(cmd);
	shell->cmds = cmd;
	// mult_word(&tmp);
	// shell->tokens = tmp;
	while (tmp)
	{
		prev = tmp;
		if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd);
		if (tmp == prev)
			tmp = tmp->next;
	}
}

void	create_token(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '|' )
	{
		add_token(shell, "|", PIPE);
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		add_token(shell, ">>", REDIRECT);
		(*i) += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(shell, ">", REDIRECT);
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(shell, "<<", HEREDOC);
		(*i) += 2;
	}
	else
		create_more(shell, input, i);
}

void	create_more(t_shell *shell, char *input, int *i)
{
	if (input[*i] == '<')
	{
		add_token(shell, "<", REDIRECT);
		(*i)++;
	}
	else if (input[*i] == '$')
	{
		add_token(shell, "$", DOLLAR);
		(*i)++;
	}
}

