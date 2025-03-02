/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:00:04 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 18:30:14 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_error_message(int err_no)
{
	if (err_no == ERR_MANY_ARGS)
		return (": too many arguments\n");
	else if (err_no == ERR_NUMERIC_ARG_REQUIRED)
		return (": numeric argument required\n");
	else if (err_no == ERR_NO_SUCH_FILEDIR)
		return (": No such file or directory\n");
	else if (err_no == ERR_IS_DIR)
		return (": is a directory\n");
	else if (err_no == ERR_IS_DIR_OR_PERMISSION)
		return (": Permission denied\n");
	else if (err_no == ERR_CMD_NOT_FOUND)
		return (": command not found\n");
	else if (err_no == ERR_UNEXPECTED_TOKEN)
		return ("syntax error near unexpected token `");
	else if (err_no == ERR_RL_EOF)
		return ("minishell: syntax error: unexpected end of file\n");
	else
		return (NULL);
}

static int	print_err_rl_eof(char *detail, char *error_message, int err_no)
{
	if (is_quote(detail[ft_strlen(detail) - 1])
		&& (ft_putstr_fd("minishell: unexpected EOF \
		while looking for matching `", 2) <= 0
			|| ft_putstr_fd(&(detail[ft_strlen(detail) - 1]), 2) <= 0
			|| ft_putstr_fd("'\n", 2) <= 0))
		return (0);
	if (ft_putstr_fd(error_message, 2) >= 0)
		return (err_no);
	return (0);
}

static int	print_error_message(int err_no, char *detail)
{
	char	*error_message;

	error_message = get_error_message(err_no);
	if (!error_message)
		return (0);
	if (err_no == ERR_UNEXPECTED_TOKEN)
	{
		if (ft_putstr_fd("minishell: ", 2) >= 0
			&& ft_putstr_fd(error_message, 2) >= 0
			&& ft_putstr_fd(detail, 2) >= 0
			&& ft_putstr_fd("'\n", 2) >= 0)
			return (err_no);
	}
	else if (err_no == ERR_RL_EOF)
		return (print_err_rl_eof(detail, error_message, err_no));
	else
	{
		if (ft_putstr_fd("minishell: ", 2) >= 0
			&& ((err_no == ERR_NUMERIC_ARG_REQUIRED
					&& write(2, "exit: ", 7)) || 1)
			&& ft_putstr_fd(detail, 2) >= 0
			&& ft_putstr_fd(error_message, 2) >= 0)
			return (err_no);
	}
	return (0);
}

int	print_user_error(t_data *data, int err_no, char *detail)
{
	int	result;

	result = print_error_message(err_no, detail);
	if (result)
		return (result);
	if (err_no == ERR_EXPORT)
		return (print_err_export(detail, err_no));
	if (err_no == ERR_UNSET)
	{
		if (ft_putstr_fd("minishell: unset: `", 2) >= 0
			&& ft_putstr_fd(detail, 2) >= 0
			&& ft_putstr_fd("': not a valid identifier\n", 2) >= 0)
			return (err_no);
	}
	if (err_no == ERR_OPEN || err_no == ERR_CHDIR)
	{
		if (ft_putstr_fd("minishell: ", 2) == -1)
			set_error(data, ERR_WRITE);
		perror(detail);
		g_status.exit = 1;
		return (errno);
	}
	print_err_no_msg(ERR_WRITE);
	exit(ERR_WRITE);
}

void	print_minishell_error(int err_no)
{
	if (err_no == ERR_MINISH_ARG)
		ft_putstr_fd("minishell: no arguments needed", 2);
	else
	{
		ft_putstr_fd("minishell: error calling ", 2);
		print_err_no_msg(err_no);
		ft_putstr_fd(" function\n", 2);
	}
}
