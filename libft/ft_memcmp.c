/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:07:49 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:45:33 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;
	size_t			i;

	if (n == 0)
		return (0);
	else
	{
		s1_tmp = (unsigned char *) s1;
		s2_tmp = (unsigned char *) s2;
		i = 0;
		while (i < n - 1 && s1_tmp[i] == s2_tmp[i])
			i++;
		return ((int)(s1_tmp[i] - s2_tmp[i]));
	}
}
