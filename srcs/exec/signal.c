/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:52:21 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 17:32:59 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include <signal.h>

void	hd_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		close (g_status.hd_fd);
		g_status.hd_fd = 0;
		g_status.exit = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(g_status.exit);
}

void	child_sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		if (!g_status.waiting_for_child)
		{
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
			g_status.exit = 1;
		}
	}
}
