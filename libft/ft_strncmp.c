/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:10 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:45:00 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		value_s1;
	int		value_s2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (INT_MIN);
	if (!s2)
		return (INT_MAX);
	if (n == 0)
		return (0);
	else
	{
		i = 0;
		while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		value_s1 = (int) s1[i];
		value_s2 = (int) s2[i];
		if (value_s1 < 0)
			value_s1 += 256;
		if (value_s2 < 0)
			value_s2 += 256;
		return (value_s1 - value_s2);
	}
}
