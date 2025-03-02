/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_strcount.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:15:29 by oladams           #+#    #+#             */
/*   Updated: 2024/01/30 17:16:10 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_strcount(t_list *list, char *str)
{
	int	i;

	i = 0;
	while (list)
	{
		if (str == NULL && (char *)(list->content) == NULL)
			i++;
		if (str && ft_strncmp(str, (char *)(list->content),
			ft_strlen(str)) == 0)
			i++;
		list = list->next;
	}
	return (i);
}
