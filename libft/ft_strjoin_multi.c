/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:37:19 by oladams           #+#    #+#             */
/*   Updated: 2024/02/03 15:35:41 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//n: nombre de strings a concatener. 
//Si n est negatif, il sera traite comme positif.
//parametres suivants:
	//si n > 0:
		//... -> chaque string a join.
		//char *str_A, char *str_B, char *str_C, etc.
	//si n < 0
		//... -> couples d'extremites 
		//de string a join.
		//char *str_A_start, char *str_A_end,
		//char *str_B_start, char *str_B_end, char *str_C_start, etc.

static char	*get_str(va_list args, int interval)
{
	char	*str;
	char	*end;
	int		max_dup;

	max_dup = INT_MAX;
	str = va_arg(args, char *);
	if (interval)
	{
		end = va_arg(args, char *);
		if (end != NULL)
			max_dup = ft_strlen(str) - ft_strlen(end);
	}
	str = ft_strndup(str, max_dup);
	return (str);
}

static char	*free_tmp1(char *output)
{
	if (output)
		free(output);
	return (NULL);
}

static char	*multi_join(int n, va_list args, int interval)
{
	char	*output;
	char	*tmp1;
	char	*tmp2;

	output = NULL;
	while (n--)
	{
		tmp1 = get_str(args, interval);
		if (!tmp1)
			return (free_tmp1(output));
		if (!output)
			output = ft_strjoin("", tmp1);
		else
		{
			tmp2 = output;
			output = ft_strjoin(output, tmp1);
			free(tmp2);
		}
		free(tmp1);
		if (!output)
			return (NULL);
	}
	return (output);
}

char	*ft_strjoin_multi(int n, ...)
{
	va_list	args;
	char	*str;
	int		interval;

	interval = 0;
	if (n < 0)
	{
		interval = 1;
		n = -n;
	}
	if (n < 2)
		return (NULL);
	va_start(args, n);
	str = multi_join(n, args, interval);
	va_end(args);
	return (str);
}
