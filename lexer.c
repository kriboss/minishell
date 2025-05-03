/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:06:45 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/03 12:28:30 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char	quoted(char *line)
{
	int i;
	char *arg;
	//int len;

	i = 0;
	//arg = malloc(sizeof(char) * len);
	while (line[i])
	{
		if (line[i] == "'")
		{
			i++;
			arg = line[i];
			while (line[i] != "'")
			{
				
			}
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int i = 0;
	
	if (argc == 2)
		quoted(argv);
	return 0;
}
