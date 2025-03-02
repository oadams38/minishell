/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:39:09 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 13:50:25 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	has_n_flag(char **args)
{
	int	i;
	int	j;
	int	n_flags;

	j = 0;
	n_flags = 0;
	while (args[j])
	{
		if (args[j][0] == '-')
		{
			i = 1;
			while (args[j][i] == 'n')
				i++;
			if (args[j][i] == '\0')
				n_flags++;
			else
				return (n_flags);
		}
		else
			return (n_flags);
		j++;
	}
	return (n_flags);
}

int	echo_bi(t_data *data, t_cmds *cmd)
{
	int	n_flags;
	int	i;

	n_flags = has_n_flag(&(cmd->exec_n_args[1]));
	i = 1;
	i += n_flags;
	while (cmd->exec_n_args[i])
	{
		if (ft_putstr_fd(cmd->exec_n_args[i], STDOUT_FILENO) == -1
			&& set_error(data, ERR_WRITE))
			return (-1);
		if (cmd->exec_n_args[i + 1])
			if (write(STDOUT_FILENO, " ", 1) < 0
				&& set_error(data, ERR_WRITE))
				return (-1);
		i++;
	}
	if (!n_flags)
		if (write(STDOUT_FILENO, "\n", 1) < 0
			&& set_error(data, ERR_WRITE))
			return (-1);
	g_status.exit = 0;
	return (0);
}
