/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 05:52:26 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 05:57:47 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_simple_cmd(t_simple_cmd *simple_cmd)
{
	int	i;

	i = 0;
	free(simple_cmd->original);
	if (simple_cmd->file_path != NULL)
		free(simple_cmd->file_path);
	if (simple_cmd->argv == NULL)
		return ;
	while (simple_cmd->argv[i] != NULL)
	{
		free(simple_cmd->argv[i]);
		i++;
	}
	free(simple_cmd->argv);
}

void	free_redirect(t_redirect *redirect)
{
	free(redirect->filename);
}

void	free_ast_node(t_ast **node)
{
	if ((*node)->type == AST_PIPE)
		;
	if ((*node)->type == AST_CMD)
		;
	if ((*node)->type == AST_SIMPLE_CMD)
		free_simple_cmd((*node)->data);
	if ((*node)->type == AST_REDIRECTS)
		;
	if ((*node)->type == AST_REDIRECT)
		free_redirect((*node)->data);
	free((*node)->data);
}

void	free_tree(t_ast **node)
{
	if ((*node)->left != NULL)
		free_tree(&(*node)->left);
	if ((*node)->right != NULL)
		free_tree(&(*node)->right);
	free_ast_node(node);
	free(*node);
}
