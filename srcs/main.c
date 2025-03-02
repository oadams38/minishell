/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:58:48 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 19:37:09 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_status	g_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	g_status.hd_fd = 0;
	g_status.exit = 0;
	g_status.waiting_for_child = 0;
	if (argc != 1)
	{
		set_error(&data, ERR_MINISH_ARG);
		print_minishell_error(data.err_no);
		do_exit(NULL);
	}
	if (struct_init(&data, env) == -1)
	{
		print_minishell_error(data.err_no);
		do_exit(&data);
	}
	launch_shell(&data);
	if (data.err_no)
		print_minishell_error(data.err_no);
	clear_data(&data);
	return (g_status.exit);
}
