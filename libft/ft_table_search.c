/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:17:53 by oladams           #+#    #+#             */
/*   Updated: 2023/11/16 18:30:32 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_table_search(char **table, char *to_find)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (table[i] && !ft_strncmp(table[i], to_find, INT_MAX))
			return (i);
		i++;
	}
	return (-1);
}
