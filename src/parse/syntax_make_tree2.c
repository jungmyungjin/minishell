/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_tree2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:04:08 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 06:21:01 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (simple_cmd == NULL)
		allocation_error();
	if (tokens.tokens[idx].type == T_WORD)
	{
		simple_cmd->original = ft_strdup(tokens.tokens[idx].str);
		if (simple_cmd->original == NULL)
			allocation_error();
		idx = add_simple_cmd_argv(tokens, simple_cmd, idx);
		*node = new_ast(simple_cmd, AST_SIMPLE_CMD);
	}
	else
		return (-1);
	return (idx);
}

int	syntax_argv(t_token_info tokens, int idx, char **args, int depth)
{
	char	*str;

	if (tokens.tokens[idx].type == T_WORD)
	{
		str = ft_strdup(tokens.tokens[idx].str);
		if (str == NULL)
			allocation_error();
		args[depth] = str;
	}
	idx++;
	if (tokens.tokens[idx].type == T_WORD)
		idx = syntax_argv(tokens, idx, args, depth + 1);
	else
		args[depth + 1] = NULL;
	return (idx);
}

t_ast	*new_ast(void *item, int type)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	if (new == NULL)
		allocation_error();
	new->left = NULL;
	new->right = NULL;
	new->data = item;
	new->type = type;
	return (new);
}

int	redirect_type(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INPUT);
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOCUMENTS);
	if (!ft_strcmp(str, ">>"))
		return (APPENDING_OUTPUT);
	return (0);
}
