/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:58:00 by apellier          #+#    #+#             */
/*   Updated: 2024/02/15 19:18:02 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# include "minishell.h"

# define STDERR 2

# define READ 0
# define WRITE 1

# define ICS_UNFINISHED	1
# define ICS_ERROR		-1
# define ICS_EOF		2

# define MAX_PATH 256

//minishell error -> end program
# define ERR_MINISH_ARG				34
# define ERR_MALLOC					35
# define ERR_WRITE					36
# define ERR_GETCWD					37
# define ERR_EXECVE					38
# define ERR_FORK					39
# define ERR_OPEN					40
# define ERR_CLOSE					41
# define ERR_PIPE					42
# define ERR_SIGACTION				43
# define ERR_CHDIR					44
# define ERR_IS_DIR					45
# define ERR_EXPORT					46
# define ERR_UNSET                  47

//user input error -> continue shell loop
# define ERR_NO_SUCH_FILEDIR		1
# define ERR_IS_DIR_OR_PERMISSION	126
# define ERR_CMD_NOT_FOUND			127 //actual code
# define ERR_NUMERIC_ARG_REQUIRED	255 //actual code
# define ERR_UNEXPECTED_TOKEN		152
# define ERR_MANY_ARGS				153
# define ERR_RL_EOF					154

//SIGNALS
# define EXIT_CTRLD					133

#endif
