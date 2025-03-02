/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:14:36 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 19:11:34 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	modify_env_value(
	t_data *data, int n_tab, char *cmd_arg, int equal_pos)
{
	char	*temp;
	char	*new_value;

	if (has_equal(data->env[n_tab]) == -1)
		temp = cmd_arg + equal_pos - 1;
	else
		temp = cmd_arg + equal_pos;
	new_value = ft_strjoin(data->env[n_tab], temp);
	if (!new_value && set_error(data, ERR_MALLOC))
		return (-1);
	my_free(data->env[n_tab]);
	data->env[n_tab] = new_value;
	return (0);
}

static int	add_env_value(t_data *data, char *cmd_arg)
{
	char	*temp;
	char	*new_value;
	int		i;

	i = 0;
	while (cmd_arg[i])
	{
		if (cmd_arg[i] == '+')
			break ;
		i++;
	}
	new_value = ft_strndup(cmd_arg, i);
	temp = new_value;
	new_value = ft_strjoin(new_value, cmd_arg + i + 1);
	my_free(temp);
	if (!new_value && set_error(data, ERR_MALLOC))
		return (-1);
	data->env = ft_table_add_back(data->env, new_value);
	my_free(new_value);
	if (!data->env && set_error(data, ERR_MALLOC))
		return (-1);
	return (0);
}

int	concatenate_to_env(t_data *data, char *cmd_arg, int equal_pos)
{
	int		n_tab;

	n_tab = is_in_tab(data->env, cmd_arg, equal_pos);
	if (n_tab >= 0)
		return (modify_env_value(data, n_tab, cmd_arg, equal_pos));
	else
		return (add_env_value(data, cmd_arg));
}
