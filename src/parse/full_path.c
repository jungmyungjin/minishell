/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:01:23 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:01:35 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(t_list *env, char *cmd)
{
	char	*current_path;
	char	*full_path;

	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		full_path = ft_strdup(cmd);
	}
	else if (ft_strncmp("./", cmd, 2) == 0)
	{
		cmd = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
		current_path = get_current_path();
		full_path = ft_strjoin(current_path, ft_strdup("/"));
		full_path = ft_strjoin(full_path, cmd);
	}
	else
	{
		full_path = get_full_path_by_env(env, cmd);
	}
	return (full_path);
}

void	set_simple_cmd_full_path(t_list *env, t_simple_cmd *simple_cmd)
{
	simple_cmd->file_path = get_full_path(env, simple_cmd->original);
}

void	set_full_path_in_tree(t_list *env, t_ast *node)
{
	if (node->left != NULL)
		set_full_path_in_tree(env, node->left);
	if (node->right != NULL)
		set_full_path_in_tree(env, node->right);
	if (node->type == AST_SIMPLE_CMD)
		set_simple_cmd_full_path(env, node->data);
}
