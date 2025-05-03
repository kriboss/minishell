/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:31:14 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/25 11:31:15 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
#include <stdio.h>

int main() {

    // Create nodes
    t_list *node1 = ft_lstnew("First");
    t_list *node2 = ft_lstnew("Second");
    t_list *node3 = ft_lstnew("Third");
    t_list *node4 = ft_lstnew("Fourth");

    // Link nodes
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    t_list *lst = ft_lstlast(node1);
    printf("nodes content:\n");
    while(node1)
    {
    	printf("%s\n", (char *)node1->content);
    	node1 = node1->next;
    }
    printf("last node: %s", (char *)lst->content);

    // Free allocated memory
    free(node3);
    free(node2);
    free(node1);

    return 0;
}*/
