/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:59:48 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 21:57:11 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (!lst || !del)
		return (1);
	node = *lst;
	while (node)
	{
		if (node->content)
			del(node->content);
		next = node->next;
		free(node);
		node = next;
	}
	*lst = NULL;
	return (1);
}
