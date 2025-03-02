/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:32:22 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 16:46:52 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_error(t_data *data, int err_no)
{
	if (data->err_no == 0)
		data->err_no = err_no;
	return (data->err_no);
}

void	print_err_no_msg(int err_no)
{
	if (err_no == ERR_MALLOC)
		ft_putstr_fd("malloc", 2);
	else if (err_no == ERR_WRITE)
		ft_putstr_fd("write", 2);
	else if (err_no == ERR_GETCWD)
		ft_putstr_fd("getcwd", 2);
	else if (err_no == ERR_EXECVE)
		ft_putstr_fd("execve", 2);
	else if (err_no == ERR_FORK)
		ft_putstr_fd("fork", 2);
	else if (err_no == ERR_OPEN)
		ft_putstr_fd("open", 2);
	else if (err_no == ERR_CLOSE)
		ft_putstr_fd("close", 2);
	else if (err_no == ERR_PIPE)
		ft_putstr_fd("pipe", 2);
	else if (err_no == ERR_SIGACTION)
		ft_putstr_fd("sigaction", 2);
	else
		ft_putstr_fd("chdir", 2);
}

int	print_err_export(char *detail, int err_no)
{
	if (ft_putstr_fd("minishell: export: `", 2) >= 0
		&& ft_putstr_fd(detail, 2) >= 0
		&& ft_putstr_fd("': not a valid identifier\n", 2) >= 0)
		return (err_no);
	print_err_no_msg(ERR_WRITE);
	exit(ERR_WRITE);
}
