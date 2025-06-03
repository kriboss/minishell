#include "minishell.h"

void create_token(t_shell *shell, char *input, int *i)
{
    if (input[*i] == '|' )
    {
        add_token(shell, "|", PIPE);
        (*i)++;
    }
    else if (input[*i] == '>' && input[*i + 1] == '>')
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
    else if (input[*i] == '<')
    {
        add_token(shell, "<", REDIRECT);
        (*i)++;
    }
}

void add_token(t_shell *shell, char *value, int type)
{
    t_token *new_token;

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

void tokenize(t_shell *shell)
{
    int i;
    char *input;

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
            int start = i;
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
