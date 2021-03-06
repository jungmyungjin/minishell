/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:01:45 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 07:45:07 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_pipeline(t_token_info tokens, int idx, t_ast **node)
{
	*node = new_ast(NULL, AST_PIPE);
	idx = syntax_cmd(tokens, idx, &(*node)->left);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_PIPE)
		idx = syntax_pipeline(tokens, idx + 1, &(*node)->right);
	return (idx);
}

int	syntax_cmd(t_token_info tokens, int idx, t_ast **node)
{
	*node = new_ast(NULL, AST_CMD);
	idx = syntax_simple_cmd(tokens, idx, &(*node)->right);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx = syntax_redirects(tokens, idx, &(*node)->left);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}

int	syntax_redirects(t_token_info tokens, int idx, t_ast **node)
{
	t_redirect	redirect;

	*node = new_ast(NULL, AST_REDIRECTS);
	idx = syntax_io_redirect(tokens, idx, &(*node)->left);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx = syntax_redirects(tokens, idx, &(*node)->right);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}

int	syntax_io_redirect(t_token_info tokens, int idx, t_ast **node)
{
	t_redirect	*redirect;

	if (tokens.tokens[idx].type == T_REDIRECT
		&& tokens.tokens[idx + 1].type == T_WORD)
	{
		redirect = (t_redirect *)malloc(sizeof(t_redirect));
		if (redirect == NULL)
			allocation_error();
		redirect->type = redirect_type(tokens.tokens[idx].str);
		redirect->filename = ft_strdup(tokens.tokens[idx + 1].str);
		if (redirect->filename == NULL)
			allocation_error();
		*node = new_ast(redirect, AST_REDIRECT);
	}
	else
		return (-1);
	idx += 2;
	return (idx);
}

int	add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx)
{
	int	i;

	if (tokens.tokens[idx + 1].type == T_WORD)
	{
		i = 0;
		while (tokens.tokens[idx + i].type == T_WORD)
			i++;
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
		if (simple_cmd->argv == NULL)
			allocation_error();
		idx = syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	else
	{
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (2));
		idx = syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	return (idx);
}
