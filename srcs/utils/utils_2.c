/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:28:42 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 18:47:29 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_double_env(t_cmd_table *cmd_table)
{
	int	env_interact;
	int	call_to_env;
	int	i;

	env_interact = 0;
	call_to_env = 0;
	i = 0;
	while (i < cmd_table->n_cmds)
	{
		if (ft_multi_strncmp(2, cmd_table->cmds[i]->executable,
				"unset", "export") >= 0)
			env_interact++;
		else if (ft_strncmp(cmd_table->cmds[i]->executable, "env", 3))
			call_to_env++;
		i++;
	}
	if ((env_interact && call_to_env) || env_interact > 1)
	{
		g_status.exit = 1;
		return (-1);
	}
	return (0);
}

static int	get_export_key_size(char **env)
{
	int	i;
	int	number_of_keys;

	i = 0;
	number_of_keys = 0;
	while (i < ft_get_table_size(env))
	{
		if (has_equal(env[i]) != -1)
			number_of_keys++;
		i++;
	}
	return (number_of_keys);
}

static int	realloc_blank_space(t_data *data)
{
	int	i;

	i = get_export_key_size(data->env);
	ft_free_tab(data->env_keys);
	ft_free_tab(data->env_values);
	data->env_keys = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_keys && set_error(data, ERR_MALLOC))
		return (-1);
	data->env_values = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_values && set_error(data, ERR_MALLOC)
		&& my_free(data->env_keys))
		return (-1);
	while (i >= 0)
	{
		data->env_keys[i] = NULL;
		data->env_values[i] = NULL;
		i--;
	}
	return (0);
}

int	process_env_entry(t_data *data, char *env_entry, int index)
{
	int		key_len;
	char	*equal_ptr;

	equal_ptr = ft_strchr(env_entry, '=');
	key_len = equal_ptr - env_entry;
	my_free(data->env_keys[index]);
	data->env_keys[index] = ft_strndup(env_entry, key_len);
	if (!data->env_keys[index] && set_error(data, ERR_MALLOC))
		return (-1);
	my_free(data->env_values[index]);
	data->env_values[index] = ft_strdup(equal_ptr + 1);
	if (!data->env_values[index] && set_error(data, ERR_MALLOC)
		&& my_free(data->env_keys[index]))
		return (-1);
	return (0);
}

int	update_env_keys_values(t_data *data)
{
	int	i;
	int	j;

	if (realloc_blank_space(data) == -1)
		return (-1);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!ft_strchr(data->env[i], '='))
		{
			i++;
			continue ;
		}
		else
		{
			if (process_env_entry(data, data->env[i], j) == -1)
				return (-1);
			j++;
			i++;
		}
	}
	return (0);
}
