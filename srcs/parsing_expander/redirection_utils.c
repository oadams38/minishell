/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:00:47 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 16:33:22 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_hd_fd(t_data *data, t_cmds *cmd)
{
	int		hd_fd;
	char	*hd_filename;

	hd_filename = ft_itoa(cmd->cmd_nb);
	if (!hd_filename && set_error(data, ERR_MALLOC))
		return (0);
	cmd->hd_path = ft_strjoin("./tmp/", hd_filename);
	free(hd_filename);
	if (!(cmd->hd_path) && set_error(data, ERR_MALLOC))
		return (0);
	hd_fd = open(cmd->hd_path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (hd_fd == -1)
		print_user_error(data, ERR_OPEN, cmd->hd_path);
	return (hd_fd);
}

static void	child_heredoc_parsing(t_data *data, char *actual_stop)
{
	char	*line;

	g_status.exit = 0;
	signal(SIGINT, hd_sigint_handler);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line_signals(0);
		if (g_status.exit == 1 || g_status.exit == 164)
		{
			close (g_status.hd_fd);
			exit(g_status.exit);
		}
		if (!line && set_error(data, ERR_MALLOC))
			exit(-1);
		if (ft_strlen(actual_stop) + 1 == ft_strlen(line)
			&& ft_strncmp(line, actual_stop, ft_strlen(actual_stop)) == 0
			&& my_free(line))
			exit(0);
		ft_putstr_fd(line, g_status.hd_fd);
	}
}

static int	read_write_lines(t_data *data, char *actual_stop, t_cmds *cmd)
{
	int		pid;
	int		status;

	g_status.hd_fd = get_hd_fd(data, cmd);
	if (g_status.hd_fd == 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_heredoc_parsing(data, actual_stop);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_g_exit_status_from_process(status);
	if (g_status.exit == -1)
		set_error(data, ERR_MALLOC);
	cmd->here_doc = g_status.hd_fd;
	g_status.hd_fd = 0;
	if (g_status.exit == 0)
		return (0);
	if (g_status.exit == 164)
		g_status.exit = 0;
	return (-1);
}

int	get_here_doc(t_data *data, t_cmds *cmd, char *stop)
{
	char	*actual_stop;
	int		ret;

	ret = 0;
	if (is_quote(stop[0]) && stop[0] == stop[ft_strlen(stop) - 1])
	{
		actual_stop = ft_strndup(stop + 1, ft_strlen(stop) - 2);
		if (!actual_stop && set_error(data, ERR_MALLOC))
			return (-1);
	}
	else
		actual_stop = stop;
	ret = read_write_lines(data, actual_stop, cmd);
	if (stop != actual_stop)
		my_free(actual_stop);
	return (ret);
}

int	get_quoteless_content(t_data *data, t_list *tokens)
{
	char	*redir_path;

	redir_path = remove_quotes(data, tokens->next->content);
	if (!redir_path)
		return (-1);
	free(tokens->next->content);
	tokens->next->content = redir_path;
	return (0);
}
