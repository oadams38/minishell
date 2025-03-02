/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:07:55 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:44:01 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	ptr = (char *) s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (ptr + i);
		i++;
	}
	if ((char) c == '\0')
		return (ptr + i);
	return (NULL);
}
