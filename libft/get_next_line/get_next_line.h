/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:21:33 by oladams           #+#    #+#             */
/*   Updated: 2024/01/16 19:25:31 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define OPEN_MAX 1024

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_buffer
{
	char	buffers[OPEN_MAX][BUFFER_SIZE + 1];
	int		index[OPEN_MAX];
}	t_buffer;

char	*get_next_line(int fd);

#endif
