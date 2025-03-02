/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:04:15 by apellier          #+#    #+#             */
/*   Updated: 2024/02/03 13:54:42 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include <stdio.h>

int	is_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.'
		|| cmd[0] == '~' || ft_strchr(cmd, '/'))
		return (1);
	return (0);
}

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		paths = ft_split(env[i] + 5, ":");
		if (paths)
			return (paths);
	}
	return (NULL);
}
