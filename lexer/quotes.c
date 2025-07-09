
#include "../include/minishell.h"

char	*extract_quoted(char *input, int *i)
{
	char	quote;
	int		j;
	int		len;
	char	*buffer;

	quote = input[*i];
	j = *i + 1;
	len = 0;
	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		return (NULL);
	while (input[j] && input[j] != quote)
	{
		if (quote == '"' && input[j] == '\\' && input[j + 1])
		{
			if (input[j + 1] == '"' || input[j + 1] == '\\'
				|| input[j + 1] == '$')
				buffer[len++] = input[++j];
			else
				buffer[len++] = input[j];
			j++;
		}
		else
			buffer[len++] = input[j++];
	}
	if (!input[j] || input[j] != quote)
	{
		free(buffer);
		printf("syntax error: unclosed quote\n");
		return (NULL);
	}
	buffer[len] = '\0';
	*i = j + 1;
	return (buffer);
}

char	*process_quotes(char *word)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(strlen(word) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			quote = word[i++];
			while (word[i] && word[i] != quote)
				result[j++] = word[i++];
			if (word[i] == quote)
				i++;
		}
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
	return (result);
}

int	in_quotes(char *input, int pos)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (i < pos)
	{
		if ((input[i] == '\'' || input[i] == '"') && current_quote == 0)
			current_quote = input[i];
		else if (input[i] == current_quote)
			current_quote = 0;
		i++;
	}
	return (current_quote != 0);
}
