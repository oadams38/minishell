/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:19:11 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 17:31:38 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_g_exit_status_from_process(int status)
{
	if (WIFEXITED(status))
		g_status.exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status.exit = WTERMSIG(status) + 128;
	else
		g_status.exit = 1;
}

static void	close_finished_pid_pipes(int *pipes, int *pids,
	int finished_pid, int n_cmds)
{
	int	i;

	if (n_cmds == 1)
		return ;
	i = 0;
	while (pids[i] != finished_pid)
		i++;
	if (i == 0)
		close_pipe(&pipes[1]);
	else if (i == n_cmds - 1)
		close_pipe(&pipes[(i - 1) * 2]);
	else
	{
		close_pipe(&pipes[(i - 1) * 2]);
		close_pipe(&pipes[i * 2 + 1]);
	}
}

void	wait_child_processes(t_cmd_table *cmd_table, int *pid)
{
	int	i;
	int	status;
	int	finished_pid;

	i = 0;
	while (i < cmd_table->n_cmds)
	{
		finished_pid = waitpid(-1, &status, 0);
		if (finished_pid == pid[cmd_table->n_cmds - 1])
			update_g_exit_status_from_process(status);
		close_finished_pid_pipes(cmd_table->pipes, pid,
			finished_pid, cmd_table->n_cmds);
		i++;
	}
}

void	close_all_pipes(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (i < (cmd_table->n_cmds - 1) * 2)
	{
		if (cmd_table->pipes[i] != -1)
			close(cmd_table->pipes[i]);
		i++;
	}
}
