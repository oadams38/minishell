/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:54:26 by apellier          #+#    #+#             */
/*   Updated: 2024/02/14 17:40:20 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_data_cmd(t_data *data)
{
	if (data->tokens)
		ft_lstclear(&(data->tokens), free);
	if (data->cmd_table)
	{
		close_fds(data->cmd_table);
		free_t_cmd_table(&(data->cmd_table));
	}
}

char	*handle_input_completion(t_data *data,
	char *total_input, char **last_input, int *input_completion_status)
{
	char	*tmp;

	*input_completion_status = token_verification(data, data->tokens);
	while (*input_completion_status == ICS_UNFINISHED)
	{
		free(*last_input);
		*last_input = read_user_input("> ");
		if (!(*last_input))
		{
			*input_completion_status = ICS_EOF;
			print_user_error(data, ERR_RL_EOF, total_input);
			return (total_input);
		}
		data->tokens = tokenize(data, *last_input);
		if (!data->tokens && my_free(total_input))
			return (NULL);
		*input_completion_status = token_verification(data, data->tokens);
		tmp = ft_strjoin(total_input, *last_input);
		if (!tmp && set_error(data, ERR_MALLOC)
			&& my_free(total_input))
			return (NULL);
		free(total_input);
		total_input = tmp;
	}
	return (total_input);
}
