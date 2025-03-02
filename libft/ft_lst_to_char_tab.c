/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_char_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:16 by oladams           #+#    #+#             */
/*   Updated: 2024/01/26 17:50:27 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_char_tab(t_list *start, t_list *end)
{
	char	**table;
	t_list	*tmp;
	int		i;

	i = 0;
	if (!start)
		return (NULL);
	tmp = start;
	while (tmp && tmp != end)
	{
		i++;
		tmp = tmp->next;
	}
	table = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (start != end)
	{
		table[i] = ft_strndup((char *)(start->content), INT_MAX);
		if (!table[i] && ft_free_tab(table))
			return (NULL);
		i++;
		start = start->next;
	}
	table[i] = NULL;
	return (table);
}
