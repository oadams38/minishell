/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellier <apellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:22:07 by oladams           #+#    #+#             */
/*   Updated: 2024/02/14 17:43:02 by apellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_pwd(t_data *data)
{
	int		i;
	char	buf[PATH_MAX];
	char	*env_line;
	char	*cwd;

	if (!getcwd(buf, PATH_MAX) && set_error(data, ERR_GETCWD))
		return (-1);
	cwd = ft_strdup(buf);
	if (!cwd && set_error(data, ERR_MALLOC))
		return (-1);
	env_line = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!env_line && set_error(data, ERR_MALLOC))
		return (-1);
	i = ft_table_search(data->env_keys, "PWD");
	if (i >= 0 && my_free(data->env[i]))
		data->env[i] = env_line;
	else
	{
		data->env = ft_table_add_back(data->env, env_line);
		free(env_line);
		if (!data->env && set_error(data, ERR_MALLOC))
			return (-1);
	}
	return (update_env_keys_values(data));
}

static void	copy_content_without_quotes(char *new_content, char *content)
{
	char	quote;
	int		i;
	int		j;

	quote = 0;
	i = 0;
	j = 0;
	while (content[i])
	{
		if ((content[i] == '"' || content[i] == '\'') && !quote)
			quote = content[i];
		else if (content[i] != quote)
		{
			new_content[j] = content[i];
			j++;
		}
		i++;
	}
	new_content[j] = '\0';
}

char	*remove_quotes(t_data *data, char *content)
{
	char	*new_content;
	int		new_len;

	if (!has_quotes(content))
		return (NULL);
	new_len = ft_strlen(content) - 2;
	new_content = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_content && set_error(data, ERR_MALLOC))
		return (NULL);
	copy_content_without_quotes(new_content, content);
	return (new_content);
}
