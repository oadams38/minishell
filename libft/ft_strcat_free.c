/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:58:03 by oladams           #+#    #+#             */
/*   Updated: 2023/11/02 19:13:26 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	my_free(void *content)
{
	if (content)
		free(content);
}

char	*ft_strcat_free(char *a, char *b)
{
	int		i;
	int		j;
	char	*str;

	if (!b)
	{
		my_free(a);
		return (NULL);
	}
	i = 0;
	if (a)
		i = (int)ft_strlen(a);
	j = (int)ft_strlen(b);
	str = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!str)
	{
		my_free(a);
		return (NULL);
	}
	if (a)
		ft_strlcpy(str, a, i + 1);
	ft_strlcpy(str + i, b, j + 1);
	my_free(a);
	my_free(b);
	return (str);
}
