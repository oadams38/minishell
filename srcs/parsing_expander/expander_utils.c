/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:23:19 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 13:59:04 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	concatenate_tokens(t_data *data)
{
	t_list	*tokens;
	t_list	*tmp;
	char	*content;
	char	*joined;

	tokens = data->tokens;
	content = (char *)(tokens->content);
	while (tokens->next != NULL)
	{
		if (ft_iswhite(content[ft_strlen(content) - 1])
			&& is_word(*(char *)(tokens->next->content)))
		{
			joined = ft_strjoin((char *)tokens->content,
					(char *)tokens->next->content);
			if (!joined && set_error(data, ERR_MALLOC))
				return ;
			free(tokens->content);
			tokens->content = joined;
			tmp = tokens->next;
			tokens->next = tokens->next->next;
			ft_lstdelone(tmp, free);
		}
		tokens = tokens->next;
		content = (char *)(tokens->content);
	}
}

static int	split_token(t_data *data,
	t_list *tokens, char **table, int tab_size)
{
	int		i;
	t_list	*tmp;
	t_list	*end;

	end = tokens->next;
	free(tokens->content);
	i = 0;
	while (i < tab_size)
	{
		if (i == 0)
			tokens->content = table[i];
		else
		{
			tmp = ft_lstnew(table[i]);
			if (!tmp && set_error(data, ERR_MALLOC))
				return (-1);
			tokens->next = tmp;
			tmp->next = end;
			tokens = tokens->next;
		}
		i++;
	}
	return (0);
}

int	maybe_split_token(t_data *data, t_list *tokens, char *content)
{
	char	**table;
	int		i;

	if (ft_strchr(content, '"') || ft_strchr(content, '\''))
		return (0);
	i = 0;
	table = ft_split(content, " \t");
	if (!table && set_error(data, ERR_MALLOC))
		return (-1);
	while (table[i])
		i++;
	if (i >= 2)
	{
		if (split_token(data, tokens, table, i) == -1)
		{
			ft_free_tab(table);
			i = -1;
		}
		else
			free(table);
	}
	else
		ft_free_tab(table);
	return (i);
}
