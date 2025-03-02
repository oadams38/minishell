/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:18 by oladams           #+#    #+#             */
/*   Updated: 2024/02/02 16:40:02 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_n_words(char const *s, char *charset)
{
	size_t	i;
	size_t	n_words;

	n_words = 0;
	if (s[0] == '\0')
		return (n_words);
	if (!ft_strchr(charset, s[0]))
		n_words++;
	i = 1;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]) && ft_strchr(charset, s[i - 1]))
			n_words++;
		i++;
	}
	return (n_words);
}

static size_t	len_wd(char const *s, size_t i, char *charset)
{
	size_t	j;

	j = 0;
	while (s[i + j] && !ft_strchr(charset, s[i + j]))
		j++;
	return (j);
}

static char	**free_tab(char **table, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (NULL);
}

static char	**fill_me_please(char **table, char const *s, char *charset)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]))
		{
			table[k] = (char *) malloc(sizeof(char)
					* (len_wd(s, i, charset) + 1));
			if (!table[k])
				return (free_tab(table, k));
			j = 0;
			while (s[i] && !ft_strchr(charset, s[i]))
				table[k][j++] = s[i++];
			table[k][j] = '\0';
			k++;
		}
		else
			i++;
	}
	table[k] = NULL;
	return (table);
}

char	**ft_split(char const *s, char *charset)
{
	size_t	n_words;
	char	**table;

	if (!s)
		return (NULL);
	n_words = get_n_words(s, charset);
	table = (char **) malloc(sizeof(char *) * (n_words + 1));
	if (!table)
		return (NULL);
	return (fill_me_please(table, s, charset));
}
