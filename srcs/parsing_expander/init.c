/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:50:36 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 16:24:34 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	helper_init_t_cmd_table(t_cmd_table *cmd_table,
	t_data *data, t_list *tokens)
{
	cmd_table->env = data->env;
	cmd_table->n_cmds = ft_lst_strcount(tokens, "|") + 1;
	cmd_table->cmds = NULL;
	cmd_table->pipes = NULL;
	cmd_table->cmds = (t_cmds **)malloc(sizeof(t_cmds *) * cmd_table->n_cmds);
	cmd_table->pipes = (int *)malloc(sizeof(int) * (cmd_table->n_cmds - 1) * 2);
}

static t_cmds	*t_cmds_new(t_data *data, int i)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd && set_error(data, ERR_MALLOC))
		return (NULL);
	cmd->executable = NULL;
	cmd->exec_n_args = NULL;
	cmd->redir = NULL;
	cmd->infile_path = NULL;
	cmd->outfile_path = NULL;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->append = 0;
	cmd->here_doc = 0;
	cmd->is_builtin = 0;
	cmd->cmd_nb = i;
	cmd->hd_path = NULL;
	return (cmd);
}

t_cmd_table	*init_t_cmd_table(t_data *data, t_list *tokens)
{
	int			i;
	t_cmd_table	*cmd_table;

	cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!cmd_table && set_error(data, ERR_MALLOC))
		return (NULL);
	helper_init_t_cmd_table(cmd_table, data, tokens);
	if (!cmd_table->cmds || !cmd_table->pipes)
	{
		free_t_cmd_table(&cmd_table);
		return (NULL);
	}
	i = -1;
	while (++i < cmd_table->n_cmds)
	{
		cmd_table->cmds[i] = t_cmds_new(data, i);
		if (!cmd_table->cmds[i])
			return (NULL);
	}
	return (cmd_table);
}
