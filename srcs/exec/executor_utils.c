/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:19:19 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 19:10:51 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_cmd(char **paths, char *cmd_arg, int i, t_data *data)
{
	char	*tmp_cmd;
	char	*cmd;

	tmp_cmd = ft_strjoin(paths[i], "/");
	if (!tmp_cmd && set_error(data, ERR_MALLOC))
		return (NULL);
	cmd = ft_strjoin(tmp_cmd, cmd_arg);
	ft_secure_free((void **)&tmp_cmd);
	if (!cmd && set_error(data, ERR_MALLOC))
		return (NULL);
	return (cmd);
}

int	exec_builtin(t_data *data, t_cmds *cmd)
{
	if (!ft_strncmp(cmd->executable, "cd", INT_MAX) && cd_bi(data, cmd))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "echo", INT_MAX)
		&& echo_bi(data, cmd))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "env", INT_MAX) && env_bi(data, cmd))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "exit", INT_MAX)
		&& exit_bi(data, cmd->exec_n_args))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "export", INT_MAX)
		&& export_bi(data, cmd->exec_n_args, 0))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "pwd", INT_MAX) && pwd_bi(data))
		return (-1);
	else if (!ft_strncmp(cmd->executable, "unset", INT_MAX)
		&& unset_bi(data, cmd))
		return (-1);
	return (0);
}

int	exec_cmd(t_data *data, t_cmds *cmd)
{
	char	**paths;
	char	*cmd_to_exec;
	int		i;

	if (!ft_strncmp(cmd->executable, "./", 2))
		return (-1);
	paths = get_paths(data->env);
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		cmd_to_exec = get_cmd(paths, cmd->exec_n_args[0], i, data);
		if (!cmd_to_exec)
			break ;
		if (!access(cmd_to_exec, X_OK))
		{
			execve(cmd_to_exec, cmd->exec_n_args, data->env);
			set_error(data, ERR_EXECVE);
			exit(g_status.exit);
		}
		ft_secure_free((void **)&cmd_to_exec);
	}
	ft_free_tab(paths);
	return (-1);
}

int	close_fds(t_cmd_table *cmd_table)
{
	int	i;

	i = -1;
	while (++i < cmd_table->n_cmds)
	{
		if (cmd_table->cmds[i]->here_doc)
		{
			if (cmd_table->cmds[i]->here_doc > 2)
				close(cmd_table->cmds[i]->here_doc);
			cmd_table->cmds[i]->here_doc = 0;
		}
		else if (cmd_table->cmds[i]->infile_fd > 2)
		{
			if (cmd_table->cmds[i]->infile_fd > 2)
				close(cmd_table->cmds[i]->infile_fd);
			cmd_table->cmds[i]->infile_fd = -1;
		}
		if (cmd_table->cmds[i]->outfile_fd > 2)
		{
			if (cmd_table->cmds[i]->outfile_fd > 2)
				close(cmd_table->cmds[i]->outfile_fd);
			cmd_table->cmds[i]->outfile_fd = -1;
		}
	}
	return (1);
}
