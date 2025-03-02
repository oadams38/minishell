/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:18 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 18:02:03 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	str = (char *) malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*trim;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
		return (ft_strnew(0));
	i = 0;
	while (s[i] && (ft_isinset(set, s[i])))
		i++;
	j = ft_strlen(s) - 1;
	while (j > 0 && (ft_isinset(set, s[j])))
		j--;
	if (j < i)
		return (ft_strnew(0));
	trim = ft_strnew(j - i + 1);
	if (!trim)
		return (NULL);
	k = 0;
	while (i <= j)
		trim[k++] = s[i++];
	return (trim);
}
