/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:00:41 by oladams           #+#    #+#             */
/*   Updated: 2024/02/02 17:33:49 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_table_dup(char **table)
{
	char	**new_table;
	int		i;
	int		n_str;

	n_str = 0;
	if (!table)
		return (NULL);
	while (table[n_str])
		n_str++;
	new_table = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (!new_table)
		return (NULL);
	ft_memset(new_table, 0, sizeof(char *) * (n_str + 1));
	i = -1;
	while (++i < n_str)
	{
		new_table[i] = ft_strndup(table[i], INT_MAX);
		if (!new_table[i])
		{
			ft_free_tab(new_table);
			return (NULL);
		}
	}
	new_table[i] = NULL;
	return (new_table);
}
