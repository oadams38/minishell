/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:33:16 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 16:06:31 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_exec(t_data *data, t_cmds *cmd)
{
	if (cmd->executable == NULL)
		exit(g_status.exit);
	exec_cmd(data, cmd);
	if (is_directory(cmd->executable))
	{
		if (ft_strchr(cmd->executable, '/')
			&& print_user_error(data, ERR_IS_DIR, cmd->executable))
			exit(ERR_IS_DIR_OR_PERMISSION);
		print_user_error(data, ERR_CMD_NOT_FOUND, cmd->executable);
		exit (ERR_CMD_NOT_FOUND);
	}
	if (!access(cmd->executable, X_OK))
		execve(cmd->executable, cmd->exec_n_args, data->env);
	if (errno == 13 && ft_strchr(cmd->executable, '/'))
	{
		print_user_error(data, ERR_IS_DIR_OR_PERMISSION, cmd->executable);
		exit(ERR_IS_DIR_OR_PERMISSION);
	}
	else if (errno == 13 || errno == 2)
	{
		print_user_error(data, ERR_CMD_NOT_FOUND, cmd->executable);
		exit(ERR_CMD_NOT_FOUND);
	}
	exit(1);
}

static int	exec_single_builtin(t_data *data, t_cmds *cmd)
{
	int	stdin_cpy;
	int	stdout_cpy;
	int	ret;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (cmd->infile_fd > 2)
	{
		dup2(cmd->infile_fd, STDIN_FILENO);
		close(cmd->infile_fd);
	}
	if (cmd->outfile_fd > 2)
	{
		dup2(cmd->outfile_fd, STDOUT_FILENO);
		close(cmd->outfile_fd);
	}
	ret = exec_builtin(data, cmd);
	dup2(stdout_cpy, STDOUT_FILENO);
	dup2(stdin_cpy, STDIN_FILENO);
	return (ret);
}

static void	exec_single_child_process(t_data *data, t_cmds *cmd)
{
	signal(SIGINT, SIG_DFL);
	if (cmd->infile_fd > 2)
	{
		dup2(cmd->infile_fd, STDIN_FILENO);
		close(cmd->infile_fd);
	}
	if (cmd->outfile_fd > 2)
	{
		dup2(cmd->outfile_fd, STDOUT_FILENO);
		close(cmd->outfile_fd);
	}
	do_exec(data, cmd);
}

static int	exec_single_cmd(t_cmds *cmd, t_data *data)
{
	int	pid;

	if (cmd->is_builtin)
		return (exec_single_builtin(data, cmd));
	pid = fork();
	if (pid == -1)
	{
		g_status.exit = 1;
		return (-1);
	}
	else if (pid == 0)
		exec_single_child_process(data, cmd);
	g_status.waiting_for_child = 1;
	wait_child_processes(data->cmd_table, &pid);
	g_status.waiting_for_child = 0;
	return (g_status.exit);
}

int	executor(t_data *data, t_cmd_table *cmd_table)
{
	int	ret;

	ret = 0;
	if (cmd_table->n_cmds == 1)
	{
		if (set_fd(cmd_table->cmds[0], data, 0) == 0
			&& cmd_table->cmds[0]->fit_for_execution)
			ret = exec_single_cmd(cmd_table->cmds[0], data);
		else
			ret = -1;
	}
	else
	{
		if (check_double_env(cmd_table) == 0
			&& create_process(cmd_table, data) == 0)
			ret = -1;
		ret = -1;
	}
	return (ret);
}
