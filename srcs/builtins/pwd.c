/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:41:40 by apellier          #+#    #+#             */
/*   Updated: 2024/02/13 18:48:30 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd_bi(t_data *data)
{
	char	*current_dir;

	current_dir = malloc(sizeof(char) * MAX_PATH);
	if (!current_dir && set_error(data, ERR_MALLOC))
		return (-1);
	if (!getcwd(current_dir, MAX_PATH))
	{
		write(2, "minishell: pwd: ", 17);
		perror("");
		g_status.exit = 1;
		free(current_dir);
		return (-1);
	}
	if (ft_putendl_fd(current_dir, STDOUT_FILENO) < 0
		&& set_error(data, ERR_WRITE))
		return (-1);
	ft_secure_free((void **)&current_dir);
	g_status.exit = 0;
	return (0);
}
