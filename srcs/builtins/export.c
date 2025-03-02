/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:45:28 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 19:10:35 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	replace_env_value(t_data *data, char **env,
	char *arg, int eq_pos)
{
	int		i;
	char	*temp;
	size_t	var_name_len;
	char	**dest;

	var_name_len = (size_t)eq_pos;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, var_name_len)
			&& (env[i][var_name_len] == '='
			|| env[i][var_name_len] == '\0'))
		{
			dest = &env[i];
			temp = ft_strdup(arg);
			if (!temp && set_error(data, ERR_MALLOC))
				return (-1);
			ft_secure_free((void **)dest);
			*dest = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	display_export(t_data *data)
{
	int		i;
	int		tab_size;
	int		*sorted_position_tab;

	tab_size = ft_get_table_size(data->env);
	sorted_position_tab = get_sorted_position_tab(data, tab_size, -1);
	if (!sorted_position_tab)
		return (-1);
	i = 0;
	while (i < tab_size)
	{
		if ((ft_putstr_fd("declare -x ",
					STDOUT_FILENO) < 0
				|| ft_putendl_fd(data->env[sorted_position_tab[i]],
					STDOUT_FILENO) < 0)
			&& my_free(sorted_position_tab)
			&& set_error(data, ERR_MALLOC))
			return (-1);
		i++;
	}
	my_free(sorted_position_tab);
	return (0);
}

static int	export_with_value(t_data *data, char *argument, int eq_pos)
{
	char	*new_value;

	if (argument[eq_pos - 1] == '+')
	{
		if (concatenate_to_env(data, argument, eq_pos + 1) == -1)
			return (-1);
	}
	else
	{
		if (replace_env_value(data, data->env, argument, eq_pos) == 0)
		{
			new_value = ft_strdup(argument);
			if (!new_value && set_error(data, ERR_MALLOC))
				return (-1);
			data->env = ft_table_add_back(data->env, new_value);
			if (!data->env && set_error(data, ERR_MALLOC))
				return (-1);
			free(new_value);
		}
	}
	return (0);
}

static int	export_no_value(t_data *data, char *argument)
{
	char	*new_value;

	new_value = ft_strdup(argument);
	if (!new_value && set_error(data, ERR_MALLOC))
		return (-1);
	data->env = ft_table_add_back(data->env, new_value);
	if (!data->env && set_error(data, ERR_MALLOC) && my_free(new_value))
		return (-1);
	my_free(new_value);
	return (0);
}

int	export_bi(t_data *data, char **exec_n_args, int i)
{
	int		eq_pos;

	g_status.exit = 0;
	if (!(exec_n_args[1]))
		return (display_export(data));
	while (exec_n_args[++i] && !data->err_no)
	{
		eq_pos = has_equal(exec_n_args[i]);
		if ((eq_pos == 0
				|| valid_export_identifier(exec_n_args[i]) == -1)
			&& print_user_error(data, ERR_EXPORT, exec_n_args[i]))
		{
			g_status.exit = 1;
			continue ;
		}
		if (eq_pos > 0)
			if (export_with_value(data, exec_n_args[i], eq_pos) == -1)
				return (-1);
		if (eq_pos <= 0 && is_in_tab(data->env, exec_n_args[i], eq_pos) == -1)
			if (export_no_value(data, exec_n_args[i]) == -1)
				return (-1);
	}
	if (update_env_keys_values(data) == -1)
		return (-1);
	return (0);
}
