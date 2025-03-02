/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:49:01 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 17:27:49 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	child_process(int n_cmd, t_cmd_table *cmd_table, t_data *data)
{
	close_unused_pipes(cmd_table, n_cmd);
	set_fd(cmd_table->cmds[n_cmd], data, n_cmd);
	pipe_redirect(cmd_table, cmd_table->cmds[n_cmd], n_cmd);
	if (cmd_table->cmds[n_cmd]->infile_fd > 2)
	{
		dup2(cmd_table->cmds[n_cmd]->infile_fd, STDIN_FILENO);
		close(cmd_table->cmds[n_cmd]->infile_fd);
	}
	if (cmd_table->cmds[n_cmd]->outfile_fd > 2)
	{
		dup2(cmd_table->cmds[n_cmd]->outfile_fd, STDOUT_FILENO);
		close(cmd_table->cmds[n_cmd]->outfile_fd);
	}
	if (cmd_table->cmds[n_cmd]->fit_for_execution)
		do_exec(data, cmd_table->cmds[n_cmd]);
	exit(g_status.exit);
}

int	manage_process(t_cmd_table *cmd_table, t_data *data, int *pid, int i)
{
	pid[i] = fork();
	if (pid[i] == -1 && set_error(data, ERR_FORK))
		return (-1);
	else if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (child_process(i, cmd_table, data) == -1)
			exit(g_status.exit);
	}
	return (0);
}

int	create_process(t_cmd_table *cmd_table, t_data *data)
{
	int	i;
	int	*pid;

	i = -1;
	pid = malloc(sizeof(int) * cmd_table->n_cmds);
	if (!pid && set_error(data, ERR_MALLOC))
		return (-1);
	if (get_pipes(cmd_table, data) == -1)
	{
		free(pid);
		return (-1);
	}
	while (++i < cmd_table->n_cmds)
		if (manage_process(cmd_table, data, pid, i) == -1)
			return (-1);
	g_status.waiting_for_child = 1;
	wait_child_processes(cmd_table, pid);
	g_status.waiting_for_child = 0;
	close_all_pipes(cmd_table);
	free(pid);
	return (0);
}
