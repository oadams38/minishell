/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:18:29 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 18:27:37 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_in_tab(char **haystack, char *needle, int needle_equal_pos)
{
	int	i;
	int	len;

	i = 0;
	if (needle_equal_pos == -1)
		len = ft_strlen(needle);
	else if (needle[needle_equal_pos - 2] == '+')
		len = ft_strlen(needle) - (ft_strlen(needle) - (needle_equal_pos - 2));
	else
		len = ft_strlen(needle) - (needle_equal_pos + 1);
	while (haystack[i])
	{
		if (!ft_strncmp(haystack[i], needle, len))
			return (i);
		i++;
	}
	return (-1);
}

int	*get_sorted_position_tab(t_data *data, int tab_size, int i)
{
	int	temp;
	int	j;
	int	*sorted_position_tab;

	sorted_position_tab = (int *)malloc(sizeof(int) * tab_size);
	if (!sorted_position_tab && set_error(data, ERR_MALLOC))
		return (NULL);
	while (++i < tab_size)
		sorted_position_tab[i] = i;
	i = -1;
	while (++i < tab_size - 1)
	{
		j = -1;
		while (++j < tab_size - i - 1)
		{
			if (ft_strncmp(data->env[sorted_position_tab[j]],
					data->env[sorted_position_tab[j + 1]], INT_MAX) > 0)
			{
				temp = sorted_position_tab[j];
				sorted_position_tab[j] = sorted_position_tab[j + 1];
				sorted_position_tab[j + 1] = temp;
			}
		}
	}
	return (sorted_position_tab);
}

int	valid_export_identifier(char *identifier)
{
	int	i;
	int	in_value;

	in_value = 0;
	i = 0;
	while (identifier[i])
	{
		if (i == 0 && !ft_isalpha(identifier[i]))
			return (-1);
		if (identifier[i] == '=')
			in_value = 1;
		if (!in_value && !ft_isalnum(identifier[i])
			&& !(identifier[i] == '+' && identifier[i + 1] == '='
				&& ft_strlen(identifier) > 2))
			return (-1);
		i++;
	}
	return (0);
}
