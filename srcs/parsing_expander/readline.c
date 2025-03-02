/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:56:31 by oladams           #+#    #+#             */
/*   Updated: 2024/02/13 23:06:12 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*read_user_input(char *prompt)
{
	char	*input;

	rl_replace_line("", 1);
	input = readline(prompt);
	if (!input)
	{
		g_status.exit = 164;
	}
	return (input);
}
