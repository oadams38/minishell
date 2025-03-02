/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:44:29 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 19:04:12 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

//variable globale
typedef struct s_status {
	int						hd_fd;
	int						exit;
	volatile sig_atomic_t	waiting_for_child;
}	t_status;

extern t_status	g_status;

//megastructure
typedef struct s_data {
	char				**env;
	char				**env_keys;
	char				**env_values;
	t_list				*tokens;
	struct s_cmd_table	*cmd_table;
	int					err_no;
}				t_data;

//commande, ses arguments et ses redir
typedef struct s_cmds {	
	char			*executable;
	char			**exec_n_args;
	char			**redir;
	char			**infile_path;
	char			**outfile_path;
	int				infile_fd;
	int				outfile_fd;
	int				fit_for_execution;
	int				append;
	int				here_doc;
	int				is_builtin;
	int				cmd_nb;
	char			*hd_path;
}				t_cmds;

//command table: contient toutes les commandes, arguments
//et redirections necessaires pour l'execution d'une entree
typedef struct s_cmd_table {
	char			**env;
	struct s_cmds	**cmds;
	int				*pipes;
	int				n_cmds;
}				t_cmd_table;

#endif
