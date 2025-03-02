/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:32:59 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 17:33:38 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	set_exit_status(t_data *data, char **exec_n_args, int *end_program)
{
	if (ft_isnum(exec_n_args[1])
		|| ((exec_n_args[1][0] == '+'
			|| exec_n_args[1][0] == '-')
		&& ft_isnum(exec_n_args[1] + 1)))
		g_status.exit = ft_atoi(exec_n_args[1]);
	else
	{
		if (print_user_error(data, ERR_NUMERIC_ARG_REQUIRED,
				exec_n_args[1]) < 0)
			return (-1);
		g_status.exit = ERR_NUMERIC_ARG_REQUIRED;
		return (0);
	}
	if (exec_n_args[1] && exec_n_args[2])
	{
		if (print_user_error(data, ERR_MANY_ARGS, "exit") < 0)
			return (-1);
		*end_program = 0;
		g_status.exit = 1;
	}
	return (0);
}

int	exit_bi(t_data *data, char **exec_n_args)
{
	int	end_program;

	end_program = 1;
	if (write(1, "exit\n", 5) < 0 && set_error(data, ERR_WRITE))
		return (-1);
	if (exec_n_args[1] && set_exit_status(data,
			exec_n_args, &end_program) == -1)
		return (-1);
	if (data->cmd_table->n_cmds == 1 && end_program)
		do_exit(data);
	return (0);
}
