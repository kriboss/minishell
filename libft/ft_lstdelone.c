/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:53 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/25 11:58:54 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free (lst);
}
/*
#include <stdio.h>
#include <stdlib.h>

void del(void *content) {
    // Free the dynamically allocated content (assuming it's a string)
    free(content);
}

int main() {
	t_list *head = ft_lstnew(ft_strdup("Primo"));
	head->next = ft_lstnew(ft_strdup("Secondo"));
	head->next->next = ft_lstnew(ft_strdup("Terzo"));

	printf("before:\n");
	t_list *current = head;
	while (current) {
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("\nafter:\n");
	ft_lstdelone(head->next->next, del);
	head->next->next = NULL;
	current = head;
	while (current) {
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstdelone(head->next, del);
	ft_lstdelone(head, del);
	return 0;
}*/
