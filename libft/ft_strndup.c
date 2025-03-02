/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:34:15 by oladams           #+#    #+#             */
/*   Updated: 2023/12/18 17:49:35 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int max)
{
	int		i;
	char	*s_dup;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (i > max)
		i = max;
	s_dup = (char *) malloc(sizeof(char) * (i + 1));
	if (!s_dup)
		return (NULL);
	i = 0;
	while (s[i] && i < max)
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
