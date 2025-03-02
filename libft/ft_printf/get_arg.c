/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:10:00 by oladams           #+#    #+#             */
/*   Updated: 2023/04/19 17:37:23 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_p(unsigned long p, int *error)
{
	int		n_printed;
	char	c;

	n_printed = 0;
	if (p >= 16)
		n_printed += print_p(p / 16, error);
	c = p % 16;
	if (c >= 10)
		c = c - 10 + 'a';
	else
		c = c + '0';
	if (!*error)
	{
		if (write(1, &c, 1) == -1)
			*error = 1;
	}
	return (n_printed + 1);
}

static int	print_x(unsigned int x, char base, int *error)
{
	int		n_printed;
	char	c;

	n_printed = 0;
	if (x >= 16)
		n_printed += print_x(x / 16, base, error);
	c = x % 16;
	if (c >= 10)
		c = c - 10 + base;
	else
		c = c + '0';
	if (!*error)
	{
		if (write(1, &c, 1) == -1)
			*error = 1;
	}
	return (n_printed + 1);
}

static int	print_nu(long long i, int *error)
{
	int		n_printed;
	char	c;

	n_printed = 0;
	if (i < 0)
	{
		i *= -1;
		if (write(1, "-", 1) == -1)
			*error = 1;
		n_printed++;
	}
	if (i >= 10)
		n_printed += print_nu(i / 10, error);
	c = i % 10 + '0';
	if (!*error)
	{
		if (write(1, &c, 1) == -1)
			*error = 1;
	}
	return (n_printed + 1);
}

int	get_arg(va_list args, char conv, int *error)
{
	if (conv == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (conv == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (conv == 'p')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		return (print_p((unsigned long)va_arg(args, void *), error) + 2);
	}
	else if (conv == 'd' || conv == 'i')
		return (print_nu(va_arg(args, int), error));
	else if (conv == 'u')
		return (print_nu(va_arg(args, unsigned int), error));
	else if (conv == 'x')
		return (print_x((unsigned int)va_arg(args, int), 'a', error));
	else if (conv == 'X')
		return (print_x((unsigned int)va_arg(args, int), 'A', error));
	return (ft_putchar('%'));
}
