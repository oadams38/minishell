/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:46:45 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 16:26:51 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//cleanup de la megastructure
int	clear_data(t_data *data)
{
	if (!data)
		return (1);
	if (data->env)
		ft_free_tab(data->env);
	if (data->env_keys)
		ft_free_tab(data->env_keys);
	if (data->env_values)
		ft_free_tab(data->env_values);
	if (data->tokens)
		ft_lstclear(&(data->tokens), free);
	if (data->cmd_table)
		free_t_cmd_table(&(data->cmd_table));
	return (1);
}

//permet de free un element dans une condition if
int	my_free(void *item)
{
	if (item)
		free(item);
	item = NULL;
	return (1);
}

int	free_t_cmds(t_cmds **cmd)
{
	if (!(*cmd))
		return (1);
	if ((*cmd)->executable)
		free((*cmd)->executable);
	if ((*cmd)->exec_n_args)
		ft_free_tab((*cmd)->exec_n_args);
	if ((*cmd)->redir)
		ft_free_tab((*cmd)->redir);
	if ((*cmd)->infile_path)
		ft_free_tab((*cmd)->infile_path);
	if ((*cmd)->outfile_path)
		ft_free_tab((*cmd)->outfile_path);
	if ((*cmd)->hd_path)
		free((*cmd)->hd_path);
	ft_bzero((*cmd), sizeof(t_cmds));
	free(*cmd);
	*cmd = NULL;
	return (1);
}

void	free_pipes(t_cmd_table **cmd_table)
{
	if ((*cmd_table)->pipes)
	{
		free((*cmd_table)->pipes);
		(*cmd_table)->pipes = NULL;
	}
}

int	free_t_cmd_table(t_cmd_table **cmd_table)
{
	int		i;

	i = 0;
	while (i < (*cmd_table)->n_cmds)
	{
		if ((*cmd_table)->cmds && (*cmd_table)->cmds[i])
		{
			free_t_cmds(&((*cmd_table)->cmds[i]));
			(*cmd_table)->cmds[i] = NULL;
		}
		i++;
	}
	if ((*cmd_table)->cmds)
		free((*cmd_table)->cmds);
	(*cmd_table)->env = NULL;
	free_pipes(cmd_table);
	free(*cmd_table);
	*cmd_table = NULL;
	return (1);
}
