/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:41:48 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 16:47:38 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_table(char **table)
{
	int	j;

	j = 0;
	if (table)
	{
		while (table[j])
		{
			free(table[j]);
			j++;
		}
		free(table);
	}
	return (1);
}

char	**create_new_table(char **table, char *str, int size)
{
	char	**new_table;

	new_table = malloc(sizeof(char *) * (size + 2));
	if (!new_table)
	{
		free(str);
		free_table(table);
		return (NULL);
	}
	return (new_table);
}

char	**ft_table_add_back(char **table, char *str)
{
	int		i;
	int		j;
	char	**new_table;

	i = 0;
	if (!str)
		return (table);
	str = ft_strndup(str, INT_MAX);
	if (!str && free_table(table))
		return (NULL);
	while (table && table[i])
		i++;
	new_table = create_new_table(table, str, i);
	if (!new_table)
		return (NULL);
	j = -1;
	while (++j < i)
		new_table[j] = table[j];
	if (table)
		free(table);
	new_table[i] = str;
	new_table[i + 1] = NULL;
	return (new_table);
}
