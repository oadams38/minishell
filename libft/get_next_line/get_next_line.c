/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:24:39 by oladams           #+#    #+#             */
/*   Updated: 2023/05/15 14:07:40 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer_leftovers(t_buffer *buffers, int fd)
{
	char	*line;
	int		i;
	int		j;

	if ((*buffers).buffers[fd][0] == '\0'
		|| (*buffers).buffers[fd][(*buffers).index[fd]] == '\0')
		return (NULL);
	i = (*buffers).index[fd];
	if (i == 0)
		return (NULL);
	j = 0;
	while (i + j < BUFFER_SIZE && (*buffers).buffers[fd][i + j] != '\n'
		&& (*buffers).buffers[fd][i + j] != '\0')
		j++;
	if ((*buffers).buffers[fd][i + j] == '\n')
		j++;
	line = (char *) malloc(sizeof(char) * (j + 1));
	if (!line)
		return (NULL);
	line[j] = '\0';
	(*buffers).index[fd] = (i + j) % BUFFER_SIZE;
	while (j--)
		line[j] = (*buffers).buffers[fd][i + j];
	return (line);
}

int	line_is_complete(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*str_extend(char *line, char buffer[BUFFER_SIZE], int ret)
{
	int		i;
	char	*out;

	i = 0;
	while (line && line[i])
		i++;
	out = (char *) malloc(sizeof(char) * (i + ret + 1));
	if (!out)
	{
		if (line)
			free(line);
		return (NULL);
	}
	i = 0;
	while (line && line[i])
	{
		out[i] = line[i];
		i++;
	}
	out[i + ret] = '\0';
	while (ret-- > 0)
		out[i + ret] = buffer[ret];
	if (line)
		free(line);
	return (out);
}

int	get_n_char_to_cat(char buffer[BUFFER_SIZE], int ret)
{
	int	i;

	i = 0;
	while (i < ret && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffers;
	char			*line;
	int				ret;
	int				n_char_to_cat;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line = get_buffer_leftovers(&buffers, fd);
	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE && !line_is_complete(line))
	{
		ret = read(fd, buffers.buffers[fd], BUFFER_SIZE);
		if (ret == -1 && line)
			free(line);
		if (ret == -1)
			return (NULL);
		if (ret == 0)
			return (line);
		buffers.buffers[fd][ret] = '\0';
		n_char_to_cat = get_n_char_to_cat(buffers.buffers[fd], ret);
		buffers.index[fd] = n_char_to_cat;
		line = str_extend(line, buffers.buffers[fd], n_char_to_cat);
	}
	return (line);
}
