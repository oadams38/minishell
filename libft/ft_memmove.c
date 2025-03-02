/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:21:50 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:43:28 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;
	size_t				i;

	dest_tmp = dest;
	src_tmp = src;
	i = 0;
	while (i < n)
	{
		if (src < dest)
			dest_tmp[n - i - 1] = src_tmp[n - i - 1];
		if (dest < src)
			dest_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
