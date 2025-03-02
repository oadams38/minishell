/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:26:36 by oladams           #+#    #+#             */
/*   Updated: 2023/05/23 18:22:17 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_n_char(long long n)
{
	size_t	n_char;

	n_char = 1;
	if (n < 0)
	{
		n *= -1;
		n_char++;
	}
	while (n >= 10)
	{
		n /= 10;
		n_char++;
	}
	return (n_char);
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		n_char;
	char		*nbr;
	long long	n_long;

	n_long = (long long) n;
	n_char = get_n_char(n_long);
	nbr = (char *) malloc(sizeof(char) * (n_char + 1));
	if (!nbr)
		return (NULL);
	nbr[0] = '0';
	nbr[n_char] = '\0';
	if (n_long < 0)
	{
		nbr[0] = '-';
		n_long *= -1;
	}
	i = n_char - 1;
	while (n_long > 0)
	{
		nbr[i] = n_long % 10 + '0';
		n_long /= 10;
		i--;
	}
	return (nbr);
}
