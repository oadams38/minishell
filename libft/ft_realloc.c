/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:08:48 by oladams           #+#    #+#             */
/*   Updated: 2023/11/20 20:24:02 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *content, size_t size)
{
	void	*new_content;

	if (!size)
		return (NULL);
	new_content = malloc(size);
	if (!new_content)
	{
		if (content)
			free(content);
		return (NULL);
	}
	ft_bzero(new_content, size);
	if (content)
	{
		ft_memmove(new_content, content, size);
		free(content);
	}
	return (new_content);
}
