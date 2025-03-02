/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:30:39 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 22:06:23 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**fill_table(t_data *data, t_list *start,
	t_list *end, char **table)
{
	int	i;

	i = 0;
	while (start != end)
	{
		if (((char *)(start->content))[0] != '\0')
		{
			if (!has_quotes((char *)(start->content)))
				table[i] = ft_strndup((char *)(start->content), INT_MAX);
			else
				table[i] = remove_quotes(data, (char *)(start->content));
			if (!table[i] && ft_free_tab(table))
				return (NULL);
			i++;
		}
		start = start->next;
	}
	table[i] = NULL;
	return (table);
}

static char	**tokens_to_table(t_data *data, t_list *start, t_list *end)
{
	char	**table;
	t_list	*tmp;
	int		i;

	i = 0;
	if (!start)
		return (NULL);
	tmp = start;
	while (tmp && tmp != end)
	{
		if (((char *)(tmp->content))[0] != '\0')
			i++;
		tmp = tmp->next;
	}
	table = (char **)malloc(sizeof(char *) * (i + 1));
	if (!table && set_error(data, ERR_MALLOC))
		return (NULL);
	return (fill_table(data, start, end, table));
}

static int	set_command_properties(t_data *data, t_cmds *cmd,
	t_list *start, t_list *end)
{
	cmd->exec_n_args = tokens_to_table(data, start, end);
	if (!cmd->exec_n_args && set_error(data, ERR_MALLOC))
		return (-1);
	cmd->executable = ft_strndup(cmd->exec_n_args[0], INT_MAX);
	if (!cmd->executable && cmd->exec_n_args[0] && set_error(data, ERR_MALLOC))
		return (-1);
	if (ft_multi_strncmp(7, cmd->executable, "echo",
			"cd", "pwd", "export", "unset", "env", "exit") >= 0)
		cmd->is_builtin = 1;
	cmd->fit_for_execution = 1;
	if (!(cmd->executable))
		cmd->fit_for_execution = 0;
	return (0);
}

static int	fill_t_cmd_table(t_data *data, t_cmd_table *cmd_table)
{
	t_list	*prev;
	t_list	*tokens;
	t_list	*tmp;
	int		i;

	prev = NULL;
	tokens = data->tokens;
	i = 0;
	while (i < cmd_table->n_cmds)
	{
		tokens = get_redir(data, prev, tokens, i);
		if (!tokens)
			return (-1);
		t_list_magic(data, &prev, &tokens, &tmp);
		if (set_command_properties(data, cmd_table->cmds[i], tmp, tokens) == -1)
			return (-1);
		prev = tokens;
		if (tokens)
			tokens = tokens->next;
		i++;
	}
	return (0);
}

t_cmd_table	*create_t_cmd_table(t_data *data, t_list *tokens)
{
	t_cmd_table	*cmd_table;

	cmd_table = init_t_cmd_table(data, tokens);
	if (!cmd_table)
		return (NULL);
	data->cmd_table = cmd_table;
	if (fill_t_cmd_table(data, cmd_table) == -1
		&& (data->err_no || g_status.exit))
	{
		close_fds(cmd_table);
		if (data->tokens)
			ft_lstclear(&(data->tokens), free);
		free_t_cmd_table(&cmd_table);
		return (NULL);
	}
	return (cmd_table);
}
