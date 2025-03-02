/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:21 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 18:10:37 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	strlen;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	strlen = ft_strlen(s);
	if ((size_t) start < strlen)
		while (s[start + i] && i < len)
			i++;
	sub = (char *) malloc(sizeof(char) * (i + 1));
	if (!sub)
		return (NULL);
	if ((size_t) start < strlen)
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			sub[i] = s[start + i];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}
