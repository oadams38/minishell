/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:03:12 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 13:37:26 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_list_magic(t_data *data,
	t_list **prev, t_list **tokens, t_list **tmp)
{
	if (!(*prev))
		*prev = *tokens;
	if (*tokens != *prev && *tokens != (*prev)->next)
	{
		if (*prev == data->tokens)
			data->tokens = *tokens;
		else
			(*prev)->next = *tokens;
	}
	*tmp = *tokens;
	while (*tokens && !is_operator((char *)((*tokens)->content)))
		*tokens = (*tokens)->next;
}
