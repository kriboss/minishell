/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:21:13 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/25 13:21:14 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		ft_lstadd_back(&new, ft_lstnew(f(lst->content)));
		if (!new)
		{
			ft_lstclear(&new, *del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new);
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
	ft_lstclear(&head, del);
	current = head;
	while (current) {
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstdelone(head->next, del);
	ft_lstdelone(head, del);
	return 0;
}*/
