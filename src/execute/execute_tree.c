/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:41:52 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 06:42:31 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_simple_cmd *simple_cmd)
{
	if (!ft_strcmp(simple_cmd->original, "cd"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "env"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "export"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "unset"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "pwd"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "echo"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "exit"))
		return (1);
	return (0);
}

void	init_mcb_in_execute(t_mcb *mcb)
{
	if (mcb->fd_input != STDIN_FILENO)
		dup2(STDIN_FILENO, mcb->fd_input);
	if (mcb->fd_output != STDOUT_FILENO)
		dup2(STDOUT_FILENO, mcb->fd_output);
}

void	next_pipe_check(t_ast *node, t_mcb *mcb)
{
	int	pipe_status;

	if (node->right != NULL && node->right->type == AST_PIPE)
	{
		pipe_status = pipe(mcb->fd);
		if (pipe_status < 0)
		{
			ft_putendl_fd("PIPE FD ERROR", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		mcb->pipe_write_end = mcb->fd[WRITE_END];
		mcb->next_pipe_check = 1;
	}
}

void	execute_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
	if (node->type == AST_PIPE)
		next_pipe_check(node, mcb);
	if (node->type == AST_REDIRECT)
		execute_redirect(node->data, mcb);
	if (node->type == AST_CMD)
		init_mcb_in_execute(mcb);
	if (node->type == AST_SIMPLE_CMD)
		execute_command(node, env, mcb);
}

void	search_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
	execute_tree(node, env, mcb);
	if (node->left != NULL)
		search_tree(node->left, env, mcb);
	if (node->right != NULL)
		search_tree(node->right, env, mcb);
}
