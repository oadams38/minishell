/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:36:56 by oladams           #+#    #+#             */
/*   Updated: 2023/04/26 15:46:40 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		get_arg(va_list args, char conv, int *error);

char	*ft_strchr(const char *s, int c);
int		ft_putstr(char *s);
int		ft_putchar(char c);

#endif
