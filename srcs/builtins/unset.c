/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:45:32 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 19:08:19 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_unset_identifier(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]))
			return (-1);
		i++;
	}
	return (0);
}

static int	remove_env(t_data *data, int key_pos)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * ft_get_table_size(data->env));
	if (!new_env && set_error(data, ERR_MALLOC))
		return (-1);
	i = -1;
	j = 0;
	while (++i < ft_get_table_size(data->env))
	{
		if (i != key_pos)
		{
			new_env[j] = data->env[i];
			j++;
		}
		else
			free(data->env[i]);
	}
	new_env[j] = NULL;
	free (data->env);
	data->env = new_env;
	if (update_env_keys_values(data) == -1)
		return (-1);
	return (0);
}

int	unset_bi(t_data *data, t_cmds *cmd)
{
	int	i;
	int	env_pos;

	i = 0;
	while (cmd->exec_n_args[i])
	{
		if (is_valid_unset_identifier(cmd->exec_n_args[i]) == -1
			&& print_user_error(data, ERR_UNSET, cmd->exec_n_args[i]))
		{
			g_status.exit = 1;
			i++;
			continue ;
		}
		env_pos = is_in_tab(data->env, cmd->exec_n_args[i], -1);
		if (env_pos >= 0)
		{
			if (remove_env(data, env_pos) == -1)
				return (-1);
		}
		i++;
	}
	g_status.exit = 0;
	return (0);
}
