/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:12:09 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:17:22 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_export_string(t_list *list_env, char *target_key)
{
	char	*line;
	t_env	*target_env;

	line = NULL;
	target_env = find_env_by_key(list_env, target_key);
	line = ft_strjoin(line, ft_strdup("declare -x "));
	line = ft_strjoin(line, ft_strdup(target_env->key));
	if (target_env->value)
	{
		line = ft_strjoin(line, ft_strdup("=\""));
		line = ft_strjoin(line, ft_strdup(target_env->value));
		line = ft_strjoin(line, ft_strdup("\""));
	}
	line = ft_strjoin(line, ft_strdup("\n"));
	return (line);
}

char	*found_next_key(t_list *env, char *prev_key)
{
	char	*result_key;

	result_key = NULL;
	while (env)
	{
		if (result_key == NULL
			&& ft_strcmp(prev_key, ((t_env *)env->content)->key) < 0)
			result_key = ((t_env *)env->content)->key;
		else
		{
			if (ft_strcmp(prev_key, ((t_env *)env->content)->key) < 0
				&& ft_strcmp(result_key, ((t_env *)env->content)->key) > 0)
				result_key = ((t_env *)env->content)->key;
		}
		env = env->next;
	}
	return (result_key);
}

char	*show_env_by_export(t_list *env)
{
	char	*prev_key;
	char	*current_key;
	char	*result;
	int		idx;

	idx = -1;
	prev_key = NULL;
	result = NULL;
	while (ft_lstsize(env) > (++idx))
	{
		current_key = found_next_key(env, prev_key);
		result = ft_strjoin(result, make_export_string(env, current_key));
		prev_key = current_key;
	}
	return (result);
}

void	div_key_value(char *arg, char **key, char **value)
{
	int	separator_idx;

	separator_idx = 0;
	while (arg[separator_idx] && arg[separator_idx] != '=' )
		separator_idx++;
	*key = ft_substr(arg, 0, separator_idx);
	if (ft_strlen(arg) - separator_idx)
		*value = ft_substr(
				arg, separator_idx + 1, ft_strlen(arg) - separator_idx);
	else
		*value = NULL;
}

void	ft_export(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int		idx;
	char	*key;
	char	*value;
	char	*output;

	idx = 0;
	if (simple_cmd->argv[1] == NULL)
	{
		output = show_env_by_export(env);
		write(mcb->fd_output, output, ft_strlen(output));
		exit(0);
	}
	while (simple_cmd->argv[++idx])
	{
		key = NULL;
		value = NULL;
		div_key_value(simple_cmd->argv[idx], &key, &value);
		if (check_env_key(key))
			env_key_error("export", key);
		else
			set_env(&env, key, value);
		free(key);
		free(value);
	}
	global.rtn = 0;
}
