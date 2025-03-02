/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:12 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:45:56 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& i + j < n
			&& haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}
