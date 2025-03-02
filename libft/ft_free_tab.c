/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:46:32 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 00:28:06 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_tab(char **table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (table[i])
		{
			free(table[i]);
			table[i] = NULL;
			i++;
		}
		free(table);
		table = NULL;
		return (1);
	}
	return (-1);
}
