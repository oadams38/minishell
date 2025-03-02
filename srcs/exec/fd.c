/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:19:56 by apellier          #+#    #+#             */
/*   Updated: 2024/02/14 21:54:40 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_valid_file(t_data *data, char *path, t_cmds *cmd, int type)
{
	int	fd;

	if (type == 1)
		fd = open(path, O_RDONLY);
	else if (type == 2 && cmd->append)
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_status.exit = 1;
		print_user_error(data, ERR_OPEN, path);
		return (-1);
	}
	return (fd);
}

static int	handle_infile_redirection(t_data *data, t_cmds *cmd, int *j)
{
	if (cmd->infile_fd > 2)
		close(cmd->infile_fd);
	cmd->infile_fd = check_valid_file(data, cmd->infile_path[*j], cmd, 1);
	if (cmd->infile_fd == -1)
		return (-1);
	(*j)++;
	return (0);
}

static int	handle_outfile_redirection(t_data *data, t_cmds *cmd, int *k)
{
	if (cmd->outfile_fd > 2)
		close(cmd->outfile_fd);
	cmd->outfile_fd = check_valid_file(data, cmd->outfile_path[*k], cmd, 2);
	if (cmd->outfile_fd == -1)
		return (-1);
	(*k)++;
	return (0);
}

static int	check_valid_redirections(t_data *data, t_cmds *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd->redir && cmd->redir[i])
	{
		if (cmd->infile_path && !ft_strncmp(cmd->redir[i],
				cmd->infile_path[j], INT_MAX))
		{
			if (handle_infile_redirection(data, cmd, &j) == -1)
				return (-1);
		}
		else if (cmd->outfile_path)
		{
			if (handle_outfile_redirection(data, cmd, &k) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	set_fd(t_cmds *cmd, t_data *data, int i)
{
	if (check_valid_redirections(data, cmd) == -1)
	{
		cmd->fit_for_execution = 0;
		return (-1);
	}
	if (i == 0 && cmd->infile_fd == -1)
		cmd->infile_fd = STDIN_FILENO;
	if (i == data->cmd_table->n_cmds - 1 && cmd->outfile_fd == -1)
		cmd->outfile_fd = STDOUT_FILENO;
	if (cmd->here_doc)
	{
		if (cmd->infile_fd > 2)
			close(cmd->infile_fd);
		close(cmd->here_doc);
		cmd->here_doc = check_valid_file(data, cmd->hd_path, cmd, 1);
		cmd->infile_fd = cmd->here_doc;
	}
	return (0);
}
