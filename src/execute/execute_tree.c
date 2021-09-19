
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

void exec_run_type(t_ast *node, t_list *env, t_mcb *mcb)
{
    if (is_built_in(node->data))
        execve_built_in(node->data, env);
    else
        exec_external(node->data, env, mcb);
}

void init_mcb_in_execute(t_mcb *mcb)
{
    if (mcb->fd_input != STDIN_FILENO)
        dup2(STDIN_FILENO, mcb->fd_input);
    if (mcb->fd_output != STDOUT_FILENO) // cmd 들어가기전에 stdout로 변경
        dup2(STDOUT_FILENO, mcb->fd_output);
}

void execute_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
    if (node->type == AST_PIPE)
        ;// set_pipe(node);
    if (node->type == AST_REDIRECT)
        execute_redirect(node->data, mcb); // redirects -> redirect -> t_redirect
    if (node->type == AST_CMD)
        init_mcb_in_execute(mcb);
    if (node->type == AST_SIMPLE_CMD)
        exec_run_type(node, env, mcb);
}

// 전위 탐색
void search_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
    execute_tree(node, env, mcb);
    if (node->left != NULL)
        search_tree(node->left, env, mcb);
    if (node->right != NULL)
        search_tree(node->right, env, mcb);
}
