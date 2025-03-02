/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strncmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:42:04 by oladams           #+#    #+#             */
/*   Updated: 2024/01/30 17:19:42 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_multi_strncmp(int n_cmp, ...)
{
	va_list	args;
	char	*str;
	int		i;

	va_start(args, n_cmp);
	i = 0;
	str = va_arg(args, char *);
	if (!str)
	{
		va_end(args);
		return (-1);
	}
	while (i < n_cmp)
	{
		if (ft_strncmp(str, va_arg(args, char *), INT_MAX) == 0)
		{
			va_end(args);
			return (i);
		}
		i++;
	}
	va_end(args);
	return (-1);
}
