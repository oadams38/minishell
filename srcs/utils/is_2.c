/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:04:31 by apellier          #+#    #+#             */
/*   Updated: 2024/02/14 17:29:02 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_word(char c)
{
	if ((c >= 1 && c <= 8)
		|| (c >= 11 && c <= 31)
		|| (c == '\'') || (c == 36) || (c == '\"') || (c == 61) || (c == 127)
		|| (c >= 42 && c <= 45)
		|| (c >= 48 && c <= 57)
		|| (c >= 63 && c <= 90)
		|| (c >= 93 && c <= 95)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2)
		|| !ft_strncmp(str, ">|", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	return (is_redir(str) + is_pipe(str));
}

int	has_equal(char *argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (argument[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
