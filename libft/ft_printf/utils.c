/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:56:43 by oladams           #+#    #+#             */
/*   Updated: 2023/04/19 16:20:49 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		i++;
	if (i > 0)
		i = (int) write(1, s, i);
	return (i);
}

int	ft_putchar(char c)
{
	return ((int) write(1, &c, 1));
}
