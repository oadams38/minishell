/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:05:50 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:45:17 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_tmp;

	s_tmp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s_tmp[i] == (unsigned char) c)
			return ((void *) s_tmp + i);
		i++;
	}
	return (NULL);
}
