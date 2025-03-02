/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:14 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:44:13 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	ptr = (char *) s;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[len - i - 1] == (char) c)
			return (ptr + len - i - 1);
		i++;
	}
	if ((char) c == '\0')
		return (ptr + i);
	return (NULL);
}
