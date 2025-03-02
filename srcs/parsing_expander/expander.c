/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:54:56 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 15:39:04 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*replace_dollar(t_data *data,
	char *content, int i, char *replacement)
{
	char	*new_content;
	int		j;

	j = 1;
	if (content[i + j] == '?')
		j++;
	else
	{
		while (ft_isalnum(content[i + j]))
			j++;
	}
	new_content = ft_strjoin_multi(-3, content, content + i,
			replacement, NULL,
			content + i + j, NULL);
	if (!new_content && set_error(data, ERR_MALLOC))
		return (NULL);
	free(content);
	return (new_content);
}

static char	*get_env_variable_value(t_data *data, char *content, int i)
{
	int		j;
	int		env_index;
	char	*potential_key;
	char	*value;

	j = 0;
	while (content[i + 1 + j] && ft_isalnum(content[i + 1 + j]))
		j++;
	potential_key = ft_strndup(content + i + 1, j);
	if ((!potential_key && set_error(data, ERR_MALLOC)))
		return (NULL);
	env_index = ft_table_search(data->env_keys, potential_key);
	free(potential_key);
	if (env_index >= 0)
	{
		value = ft_strndup(data->env_values[env_index], INT_MAX);
		if (!value && set_error(data, ERR_MALLOC))
			return (NULL);
		return (value);
	}
	value = ft_strndup("", INT_MAX);
	if (!value && set_error(data, ERR_MALLOC))
		return (NULL);
	return (value);
}

static char	*process_dollar_replacement(t_data *data, char *content, int *i)
{
	char	*replacement_str;
	char	*new_content;

	if (content[*i + 1] == '?')
	{
		replacement_str = ft_itoa(g_status.exit);
		if (!replacement_str)
			set_error(data, ERR_MALLOC);
	}
	else
		replacement_str = get_env_variable_value(data, content, *i);
	if (data->err_no)
		return (NULL);
	if (replacement_str)
	{
		new_content = replace_dollar(data, content, *i, replacement_str);
		free(replacement_str);
		*i = 0;
		return (new_content);
	}
	(*i)++;
	return (content);
}

static int	maybe_replace_active_dollar(t_data *data,
	t_list *tokens, char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
			return (0);
		if (content[i] == '$' && (ft_isalnum(content[i + 1])
				|| content[i + 1] == '?'))
		{
			content = process_dollar_replacement(data, content, &i);
			if (!content || data->err_no)
				return (-1);
		}
		else
			i++;
	}
	tokens->content = content;
	return (0);
}

void	expand(t_data *data)
{
	char	*prev_content;
	t_list	*tokens;

	(void)data;
	if (update_env_keys_values(data) == -1)
		return ;
	tokens = data->tokens;
	prev_content = (char *)(tokens->content);
	while (tokens)
	{
		if (ft_strncmp("<<", prev_content, 2) != 0
			&& maybe_replace_active_dollar(data,
				tokens, tokens->content) == -1)
			return ;
		if (maybe_split_token(data, tokens, tokens->content) == -1)
			return ;
		prev_content = (char *)(tokens->content);
		tokens = tokens->next;
	}
	concatenate_tokens(data);
}
