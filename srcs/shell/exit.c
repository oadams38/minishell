/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:26:38 by oladams           #+#    #+#             */
/*   Updated: 2024/02/03 13:37:26 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//a appeler lors de signal type CTRL+D ou "exit"
void	do_exit(t_data *data)
{
	if (data)
		clear_data(data);
	exit(g_status.exit);
}
