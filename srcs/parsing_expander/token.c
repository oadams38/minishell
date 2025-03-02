/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:26:19 by oladams           #+#    #+#             */
/*   Updated: 2024/02/13 19:18:25 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_verification(t_data *data, t_list *tokens)
{
	char	*content;
	char	*next_content;

	if (is_pipe((char *)(tokens->content))
		&& print_user_error(data,
			ERR_UNEXPECTED_TOKEN, (char *)(tokens->content)))
		return (ICS_ERROR);
	while (tokens->next)
	{
		content = tokens->content;
		next_content = tokens->next->content;
		if (check_is(data, content, next_content) == -1)
			return (ICS_ERROR);
		tokens = tokens->next;
	}
	content = tokens->content;
	if (is_redir(content)
		&& print_user_error(data, ERR_UNEXPECTED_TOKEN, "newline"))
		return (ICS_ERROR);
	if (is_pipe(content) || has_unclosed_quote(content))
		return (ICS_UNFINISHED);
	return (0);
}

static char	*create_new_content(t_data *data, char *content, char *user_input)
{
	int		j;
	char	*added_material;
	char	*new_content;

	j = 0;
	while (user_input[j] && user_input[j] != content[0])
		j++;
	if (user_input[j] == content[0])
		j++;
	added_material = ft_strndup(user_input, j);
	if (!added_material && set_error(data, ERR_MALLOC))
		return (NULL);
	new_content = ft_strjoin_multi(3, content, "\n", added_material);
	if (!new_content && my_free(added_material) && set_error(data, ERR_MALLOC))
		return (NULL);
	free(added_material);
	return (new_content);
}

static int	deal_unclosed_quote(t_data *data, t_list *last_tk,
	char *user_input, int *i)
{
	char	*content;
	char	*new_content;
	size_t	len_content;
	size_t	len_new_content;

	if (!last_tk)
		return (0);
	content = (char *)(last_tk->content);
	if (has_unclosed_quote(content))
	{
		new_content = create_new_content(data, content, user_input);
		if (!new_content)
			return (-1);
		len_content = ft_strlen(content);
		len_new_content = ft_strlen(new_content);
		free(last_tk->content);
		last_tk->content = new_content;
		*i = len_new_content - len_content - 1;
	}
	return (0);
}

static t_list	*process_tokenization(t_data *data, char *user_input,
	int *index, t_list **tokens)
{
	t_list	*tmp;
	char	*str;

	if (!(data->tokens))
		tokens = &(data->tokens);
	while (user_input[*index])
	{
		if (is_operator_char(user_input[*index]))
			str = extract_operator(user_input, index);
		else
			str = extract_word(user_input, index, 0);
		if (!str && set_error(data, ERR_MALLOC) && ft_lstclear(tokens, free))
			return (NULL);
		tmp = ft_lstnew(str);
		if (!tmp && set_error(data, ERR_MALLOC)
			&& my_free(str) && ft_lstclear(tokens, free))
			return (NULL);
		ft_lstadd_back(tokens, tmp);
		while (ft_iswhite(user_input[*index]))
			(*index)++;
	}
	return (*tokens);
}

t_list	*tokenize(t_data *data, char *user_input)
{
	int		i;
	t_list	*tokens;

	i = 0;
	if (data->tokens)
		tokens = data->tokens;
	else
		tokens = NULL;
	if (deal_unclosed_quote(data, ft_lstlast(tokens), user_input, &i) == -1)
		return (NULL);
	while (ft_iswhite(user_input[i]))
		i++;
	if (process_tokenization(data, user_input, &i, &tokens) == NULL)
		return (NULL);
	return (data->tokens);
}
