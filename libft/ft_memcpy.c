/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:07:51 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 18:07:31 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	if (!dest && !src)
		return (dest);
	dest_tmp = dest;
	src_tmp = src;
	while (n--)
		dest_tmp[n] = src_tmp[n];
	return (dest);
}
