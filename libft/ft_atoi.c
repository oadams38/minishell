/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:46:36 by oladams           #+#    #+#             */
/*   Updated: 2023/04/11 16:26:20 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	parse_prefix(const char *s, size_t *i, int *p_sign)
{
	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32)
		*i = *i + 1;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			*p_sign = -1;
		*i = *i + 1;
	}
}

static void	parse_number(const char *s, int *res, size_t *i, size_t *n_digits)
{
	while (ft_isdigit(s[*i]))
	{
		*res = *res * 10 + s[*i] - '0';
		if (!(s[*i] == '0' && *n_digits == 0))
			*n_digits = *n_digits + 1;
		*i = *i + 1;
	}
}

static int	get_actual_result(const char *s, int res, size_t n_digits, int sign)
{
	if (n_digits > 19
		|| (n_digits == 19
			&& ft_strncmp(s, "9223372036854775808", 19) > 0)
		|| (n_digits == 19
			&& ft_strncmp(s, "9223372036854775808", 19) == 0 && sign == 1))
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	else if (-res == -2147483648 && sign == -1)
		return (-2147483648);
	else
		return (res * sign);
}

int	ft_atoi(const char *s)
{
	int		res;
	int		sign;
	size_t	i;
	size_t	n_digits;

	res = 0;
	sign = 1;
	i = 0;
	parse_prefix(s, &i, &sign);
	n_digits = 0;
	parse_number(s, &res, &i, &n_digits);
	res = get_actual_result(s + i - n_digits, res, n_digits, sign);
	return (res);
}
