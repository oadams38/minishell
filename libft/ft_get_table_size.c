/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_table_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:00:52 by oladams           #+#    #+#             */
/*   Updated: 2023/11/29 20:03:43 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_table_size(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return (-1);
	while (table[i])
		i++;
	return (i);
}
