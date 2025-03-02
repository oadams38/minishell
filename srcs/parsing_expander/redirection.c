/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:17:18 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 16:24:54 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	fill_t_cmds(t_data *data, char ***path_table,
	char *path, char ***redir)
{
	*path_table = ft_table_add_back(*path_table, path);
	if (!(*path_table) && set_error(data, ERR_MALLOC))
		return (-1);
	*redir = ft_table_add_back(*redir, path);
	if (!(*redir) && set_error(data, ERR_MALLOC))
		return (-1);
	return (0);
}

static int	extract_redirection(t_data *data,
	t_cmds *command, t_list *tokens, char *path)
{
	char	*redir;

	redir = (char *)(tokens->content);
	if (!ft_strncmp(redir, ">", 1))
	{
		command->append = 0;
		fill_t_cmds(data, &(command->outfile_path), path, &(command->redir));
		if (!ft_strncmp(redir, ">>", 2))
			command->append = 1;
	}
	else if (!ft_strncmp(redir, "<", 1))
	{
		if (command->here_doc)
			command->here_doc = 0;
		if (!ft_strncmp(redir, "<<", 2))
		{
			if (get_here_doc(data, command, path) == -1)
				return (-1);
		}
		else
			fill_t_cmds(data, &(command->infile_path), path, &(command->redir));
	}
	if (data->err_no)
		return (-1);
	return (0);
}

static void	save_token_addresses(t_list **p_tk, t_list **tk, t_list **c_st)
{
	if (*p_tk)
		(*p_tk)->next = (*tk)->next->next;
	if (!*p_tk || *tk == *c_st)
		*c_st = (*tk)->next->next;
}

static int	free_used_tokens(t_data *data,
	t_list **p_tk, t_list **tk, t_list **c_st)
{
	ft_lstdelone((*tk)->next, free);
	ft_lstdelone(*tk, free);
	if (*p_tk)
		*tk = (*p_tk)->next;
	else
	{
		data->tokens = *c_st;
		*tk = *c_st;
	}
	return (1);
}

t_list	*get_redir(t_data *data, t_list *previous_token, t_list *tokens, int i)
{
	t_list		*cmd_start;

	cmd_start = tokens;
	while (tokens && tokens->next != NULL
		&& ((char *)(tokens->content))[0] != '|')
	{
		if (is_redir((char *)(tokens->content)))
		{
			save_token_addresses(&previous_token, &tokens, &cmd_start);
			if (has_quotes((char *)(tokens->next->content))
				&& get_quoteless_content(data, tokens) == -1)
				return (NULL);
			if (extract_redirection(data, (data->cmd_table->cmds)[i],
				tokens, tokens->next->content) == -1
				&& free_used_tokens(data, &previous_token, &tokens, &cmd_start))
				return (NULL);
			free_used_tokens(data, &previous_token, &tokens, &cmd_start);
		}
		else
		{
			previous_token = tokens;
			tokens = tokens->next;
		}
	}
	return (cmd_start);
}
