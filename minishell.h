/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:22:00 by oladams           #+#    #+#             */
/*   Updated: 2024/02/15 19:18:14 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <term.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "structures.h"
# include "macro.h"

//builtins/*.c
int				cd_bi(t_data *data, t_cmds *cmd);
int				echo_bi(t_data *data, t_cmds *cmd);
int				env_bi(t_data *data, t_cmds *cmd);
int				exit_bi(t_data *data, char **exec_n_args);
int				export_bi(t_data *data, char **exec_n_args, int i);
int				pwd_bi(t_data *data);
int				unset_bi(t_data *data, t_cmds *cmd);

//builtins/export_concat.c
int				concatenate_to_env(t_data *data, char *cmd_arg, int equal_pos);

//builtins/export_utils.c
int				is_in_tab(char **haystack, char *needle, int needle_equal_pos);
int				*get_sorted_position_tab(t_data *data, int tab_size, int i);
int				valid_export_identifier(char *identifier);

//exec/executor.c
int				executor(t_data *data, t_cmd_table *cmd_table);
void			do_exec(t_data *data, t_cmds *cmd);

//exec/executor_utils.c
int				exec_builtin(t_data *data, t_cmds *cmd);
int				exec_cmd(t_data *data, t_cmds *cmd);
int				close_fds(t_cmd_table *cmd_table);

//exec/fd.c
int				set_fd(t_cmds *cmd, t_data *data, int i);

//exec/parent_process.c
void			update_g_exit_status_from_process(int status);
void			wait_child_processes(t_cmd_table *cmd_table, int *pid);
void			close_all_pipes(t_cmd_table *cmd_table);

//exec/path.c
char			**get_paths(char **env);
int				is_path(char *cmd);

//exec/pipe.c
int				get_heredoc_pipes(t_cmd_table *cmd_table, t_data *data);
int				get_pipes(t_cmd_table *cmd_table, t_data *data);
int				close_unused_pipes(t_cmd_table *cmd_table, int n_cmd);
void			pipe_redirect(t_cmd_table *cmd_table, t_cmds *cmd, int n_cmd);
void			close_pipe(int *pipe_fd);

//exec/process.c
int				create_process(t_cmd_table *cmd_table, t_data *data);
int				child_process(int n_cmd, t_cmd_table *cmd_table, t_data *data);

//exec/signal.c
void			hd_sigint_handler(int sig);
void			child_sigint_handler(int sig); //////////
void			child_sigquit_handler(int sig);
void			sigint_handler(int signum);

//parsing_expander/cmd_table*.c
void			t_list_magic(t_data *data,
					t_list **prev, t_list **tokens, t_list **tmp);
t_cmd_table		*create_t_cmd_table(t_data *data, t_list *tokens);

//parsing_expander/expander*.c
void			concatenate_tokens(t_data *data);
int				maybe_split_token(t_data *data, t_list *tokens, char *content);
void			expand(t_data *data);

//parsing_expander/init*.c
int				struct_init(t_data *data, char **env);
t_cmd_table		*init_t_cmd_table(t_data *data, t_list *tokens);

//parsing_expander/readline.c
char			*read_user_input(char *prompt);

//parsing_expander/redirection.c
t_list			*get_redir(t_data *data, t_list *prev,
					t_list *tokens, int i);

//parsing_expander/redirection_utils.c
int				get_here_doc(t_data *data, t_cmds *cmd, char *stop);
int				get_quoteless_content(t_data *data, t_list *tokens);

//parsing_expander/token*.c
t_list			*tokenize(t_data *data, char *user_input);
int				check_is(t_data *data, char *content, char *next_content);
char			*extract_word(char *user_input, int *i, int j);
char			*extract_operator(char *user_input, int *i);
int				token_verification(t_data *data, t_list *tokens);

//shell/clear.c
int				clear_data(t_data *data);
int				my_free(void *item);
int				free_tab(char **table);
int				free_t_cmd_table(t_cmd_table **cmd_table);
int				free_t_cmds(t_cmds **cmds);

//shell/error*.c
int				print_user_error(t_data *data, int err_no, char *detail);
void			print_minishell_error(int err_no);

//shell/error_utils.c
int				print_err_export(char *detail, int err_no);
void			print_err_no_msg(int err_no);
int				set_error(t_data *data, int error_nb);

//shell/exit.c
void			do_exit(t_data *data);

//shell/shell*.c
void			clean_data_cmd(t_data *data);
char			*handle_input_completion(t_data *data,
					char *total_input, char **last_input,
					int *input_completion_status);
void			launch_shell(t_data *data);

//utils/is*.c
int				is_operator_char(char c);
int				is_quote(char c);
int				has_quotes(char *str);
int				has_unclosed_quote(char *str);
int				is_directory(const char *file_name);
int				is_word(char c);
int				is_redir(char *str);
int				is_pipe(char *str);
int				is_operator(char *c);
int				has_equal(char *argument);
int				is_in_tab(char **haystack, char *needle, int needle_equal_pos);

//utils/utils*.c
int				update_env_keys_values(t_data *data);
int				update_pwd(t_data *data);
char			*remove_quotes(t_data *data, char *content);
int				check_double_env(t_cmd_table *cmd_table);
char			*get_next_line_signals(int fd);

#endif
