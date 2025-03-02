/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:55:38 by apellier          #+#    #+#             */
/*   Updated: 2024/02/14 17:32:10 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	set_null_t_data(t_data *data)
{
	data->env = NULL;
	data->env_keys = NULL;
	data->env_values = NULL;
	data->tokens = NULL;
	data->cmd_table = NULL;
}

static char	**set_env(t_data *data, char **env)
{
	char	**minish_env;
	int		i;

	minish_env = ft_table_dup(env);
	if (!minish_env && set_error(data, ERR_MALLOC))
		return (NULL);
	data->env = minish_env;
	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PWD=", 4))
		i++;
	if (data->env[i])
		return (data->env);
	update_pwd(data);
	return (data->env);
}

int	struct_init(t_data *data, char **env)
{
	set_null_t_data(data);
	data->err_no = 0;
	data->env = set_env(data, env);
	if (data->env)
	{
		if (update_env_keys_values(data) == -1)
			return (-1);
	}
	else
	{
		clear_data(data);
		return (-1);
	}
	return (0);
}
