/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:45:21 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 18:42:57 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_bi(t_data *data, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->exec_n_args[1])
	{
		if (print_user_error(data, ERR_MANY_ARGS, "env") < 0)
			return (-1);
		g_status.exit = 1;
		return (0);
	}
	while (data->env_keys[i])
	{
		if (ft_putstr_fd(data->env_keys[i], STDOUT_FILENO) < 0
			&& set_error(data, ERR_WRITE))
			return (-1);
		if (ft_putchar_fd('=', STDOUT_FILENO) < 0
			&& set_error(data, ERR_WRITE))
			return (-1);
		if (ft_putendl_fd(data->env_values[i], STDOUT_FILENO) < 0
			&& set_error(data, ERR_WRITE))
			return (-1);
		i++;
	}
	g_status.exit = 0;
	return (0);
}
