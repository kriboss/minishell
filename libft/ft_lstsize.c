/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:07:09 by kbossio           #+#    #+#             */
/*   Updated: 2024/11/25 11:07:10 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
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

    // Test ft_lstsize
    int size = ft_lstsize(node1);
    printf("List size: %d\n", size);
    printf("nodes content:\n");
    while(node1)
    {
    	printf("%s\n", (char *)node1->content);
    	node1 = node1->next;
    }

    // Free allocated memory
    free(node4);
    free(node3);
    free(node2);
    free(node1);

    return 0;
}*/
