/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:14 by oladams           #+#    #+#             */
/*   Updated: 2024/02/03 13:37:26 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_operator_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

int	has_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

int	has_unclosed_quote(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == in_quote)
				in_quote = 0;
			else if (!in_quote)
				in_quote = (int)(str[i]);
		}
		i++;
	}
	return (in_quote);
}

int	is_directory(const char *file_name)
{
	struct stat	path;

	stat(file_name, &path);
	return (S_ISDIR(path.st_mode));
}
