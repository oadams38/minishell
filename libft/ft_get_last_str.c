/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:30:18 by oladams           #+#    #+#             */
/*   Updated: 2024/01/30 17:15:44 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_last_str(char **table)
{
	int	i;

	i = 0;
	if (!table || !table[0])
		return (NULL);
	while (table[i])
		i++;
	return (table[i - 1]);
}
