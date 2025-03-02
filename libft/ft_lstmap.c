/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:00:03 by oladams           #+#    #+#             */
/*   Updated: 2023/04/10 16:21:22 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*init_list(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	void	*mapped_content;

	mapped_content = f(lst->content);
	if (!mapped_content)
		return (NULL);
	node = ft_lstnew(mapped_content);
	if (!node)
	{
		del(mapped_content);
		return (NULL);
	}
	return (node);
}

static t_list	*free_list(t_list *res, void *content, void (*del)(void *))
{
	del(content);
	ft_lstclear(&res, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;
	void	*mapped_content;

	if (!lst || !f || !del)
		return (NULL);
	res = init_list(lst, f, del);
	if (!res)
		return (NULL);
	node = res;
	while (lst->next)
	{
		mapped_content = f(lst->next->content);
		if (!mapped_content)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&node, ft_lstnew(mapped_content));
		if (!node->next)
			return (free_list(res, mapped_content, del));
		node = node->next;
		lst = lst->next;
	}
	return (res);
}
