/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:07:28 by apellier          #+#    #+#             */
/*   Updated: 2024/02/14 16:23:59 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe_fd)
{
	if (*pipe_fd != -1)
	{
		close(*pipe_fd);
		*pipe_fd = -1;
	}
}

void	pipe_redirect(t_cmd_table *cmd_table, t_cmds *cmd, int cmd_nb)
{
	int	*pipes;

	pipes = cmd_table->pipes;
	if (cmd->infile_fd <= 2 && cmd_nb != 0)
		cmd->infile_fd = pipes[(cmd_nb - 1) * 2];
	else if (cmd_nb != 0)
		close_pipe(&(pipes[(cmd_nb - 1) * 2]));
	if (!(cmd_nb == cmd_table->n_cmds - 1))
	{
		if (cmd->outfile_fd <= 2)
			cmd->outfile_fd = pipes[cmd_nb * 2 + 1];
		else
			close_pipe(&(pipes[cmd_nb * 2 + 1]));
	}
}

int	get_pipes(t_cmd_table *cmd_table, t_data *data)
{
	int	i;

	i = 0;
	while (i < cmd_table->n_cmds - 1)
	{
		if (pipe(cmd_table->pipes + i * 2) == -1
			&& set_error(data, ERR_PIPE))
			return (-1);
		i++;
	}
	return (0);
}

int	close_unused_pipes(t_cmd_table *cmd_table, int cmd_nb)
{
	int	i;

	i = 0;
	while (i < (cmd_table->n_cmds - 1) * 2)
	{
		if (cmd_nb == 0 && i == 1)
			i++;
		else if (cmd_nb == cmd_table->n_cmds - 1 && i == (cmd_nb - 1) * 2)
			i++;
		else if (i == (cmd_nb - 1) * 2 || i == (cmd_nb * 2 + 1))
			i++;
		else
		{
			close(cmd_table->pipes[i]);
			cmd_table->pipes[i] = -1;
			i++;
		}
	}
	return (0);
}
