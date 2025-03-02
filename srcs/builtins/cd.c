/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:12:12 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 16:52:22 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cd_home(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_keys[i])
	{
		if (!ft_strncmp(data->env_keys[i], "HOME", 4)
			&& data->env_keys[i][4] == 0)
		{
			if (chdir(data->env_values[i]) < 0 || update_pwd(data) < 0)
			{
				write(2, "minishell: cd: ", 16);
				perror("");
				g_status.exit = 1;
				return (-1);
			}
			return (0);
		}
		i++;
	}
	write(2, "minishell: cd: HOME not set\n", 29);
	g_status.exit = 1;
	return (-1);
}

int	cd_bi(t_data *data, t_cmds *cmd)
{
	if (!cmd->exec_n_args[1])
		return (cd_home(data));
	if (access(cmd->exec_n_args[1], F_OK) != 0)
	{
		write(2, "minishell: cd: ", 16);
		perror(cmd->exec_n_args[1]);
		g_status.exit = 1;
		return (0);
	}
	if (chdir(cmd->exec_n_args[1]) < 0)
	{
		write(2, "minishell: cd: ", 16);
		perror(cmd->exec_n_args[1]);
		g_status.exit = 1;
		return (-1);
	}
	if (update_pwd(data) < 0)
	{
		write(2, "update_pwd failed\n", 18);
		return (-1);
	}
	g_status.exit = 0;
	return (0);
}
