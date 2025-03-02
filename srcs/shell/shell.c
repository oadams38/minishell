/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:23:50 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 22:06:07 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*initialize_total_input(t_data *data, char **last_input)
{
	char	*total_input;

	*last_input = read_user_input("minishell-49.3$ ");
	if (g_status.exit == 164)
	{
		ft_putstr_fd("exit\n", 2);
		g_status.exit = 0;
		do_exit(data);
	}
	if (*last_input && (*last_input)[0] == '\0')
	{
		my_free(*last_input);
		return (NULL);
	}
	total_input = ft_strndup(*last_input, INT_MAX);
	if (!total_input)
	{
		set_error(data, ERR_MALLOC);
		my_free(*last_input);
		return (NULL);
	}
	return (total_input);
}

static t_list	*tokenize_user_input(t_data *data)
{
	char	*last_input;
	char	*total_input;
	int		input_completion_status;

	last_input = NULL;
	total_input = initialize_total_input(data, &last_input);
	if (!total_input)
		return (NULL);
	if (tokenize(data, last_input) == NULL
		&& my_free(last_input) && my_free(total_input))
		return (NULL);
	total_input = handle_input_completion(data, total_input,
			&last_input, &input_completion_status);
	if (!total_input && my_free(last_input))
		return (NULL);
	add_history(total_input);
	if (input_completion_status == ICS_EOF
		|| input_completion_status == ICS_ERROR)
	{
		g_status.exit = 258;
		clean_data_cmd(data);
	}
	my_free(last_input);
	my_free(total_input);
	return (data->tokens);
}

void	launch_shell(t_data *data)
{
	while (!data->err_no)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		data->tokens = tokenize_user_input(data);
		if (!(data->tokens) && !data->err_no)
			continue ;
		if (!data->err_no)
			expand(data);
		if (!data->err_no)
			data->cmd_table = create_t_cmd_table(data, data->tokens);
		signal(SIGQUIT, child_sigquit_handler);
		if (data->cmd_table)
			executor(data, data->cmd_table);
		clean_data_cmd(data);
	}
}
