/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:35:29 by oladams           #+#    #+#             */
/*   Updated: 2023/04/19 17:37:21 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_print_chars(char *s, size_t *p_i)
{
	int	j;

	j = 0;
	while (s[j] && s[j] != '%')
		j++;
	j = (int) write(1, s, j);
	if (j == -1)
		return (-1);
	*p_i += j;
	return (j);
}

static int	ft_print_arg(va_list args, char *s, size_t *p_i)
{
	int		error;
	int		n_printed;	
	char	conversion;
	size_t	j;

	j = 0;
	if (!s[0])
		return (0);
	conversion = s[j];
	if (!s[j])
	{
		*p_i += j + 1;
		return (0);
	}
	if (!ft_strchr("cspdiuxX%", conversion))
		return (-1);
	*p_i += j + 2;
	error = 0;
	n_printed = get_arg(args, conversion, &error);
	if (error)
		return (-1);
	return (n_printed);
}

static int	parse_and_convert(const char *s, va_list args)
{
	size_t	i;
	int		n_printed;
	int		print_return;

	n_printed = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
			print_return = ft_print_chars((char *) s + i, &i);
		else
			print_return = ft_print_arg(args, (char *) s + i + 1, &i);
		if (print_return == -1)
			return (-1);
		else
			n_printed += print_return;
	}
	return (n_printed);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			n_printed;

	if (!s)
		return (-1);
	if (!s[0])
		return (0);
	va_start(args, s);
	n_printed = parse_and_convert(s, args);
	va_end(args);
	return (n_printed);
}
