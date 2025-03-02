/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:56:32 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 14:07:04 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_operator(char *user_input, int *i)
{
	int		j;
	char	*str;

	j = is_operator(user_input + *i);
	str = ft_strndup(user_input + *i, j);
	if (!str)
		return (NULL);
	*i = *i + j;
	return (str);
}

char	*extract_word(char *user_input, int *i, int j)
{
	int		in_quote;
	char	*extract;

	in_quote = 0;
	while (user_input[*i + j] && (!is_operator_char(user_input[*i + j])
			|| in_quote)
		&& ((ft_iswhite(user_input[*i + j]) && in_quote)
			|| !ft_iswhite(user_input[*i + j])))
	{
		if (is_quote(user_input[*i + j]))
		{
			if (!in_quote)
				in_quote = user_input[*i + j];
			else if (user_input[*i + j] == in_quote)
				in_quote = 0;
		}
		j++;
	}
	extract = ft_strndup(user_input + *i, j);
	*i = *i + j;
	return (extract);
}

int	check_is(t_data *data, char *content, char *next_content)
{
	if (((is_redir(content)
				&& (is_pipe(next_content) || is_redir(next_content)))
			|| (is_pipe(content) && is_pipe(next_content)))
		&& print_user_error(data, ERR_UNEXPECTED_TOKEN, next_content))
		return (-1);
	return (0);
}
