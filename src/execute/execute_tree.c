
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

void exec_run_type(t_ast *node, t_list *env)
{
    if (is_built_in(node->data))
        execve_built_in(node->data, env);
    else
        exec_external(node->data, env);
}

void execute_tree(t_ast *node, t_list *env)
{
    if (node->type == AST_PIPE)
        ;//execute_pipe();
    if (node->type == AST_REDIRECT)
        ;//execute_redirect();
    if (node->type == AST_CMD)
        ;//execute_cmd();
    if (node->type == AST_SIMPLE_CMD)
        ;//exec_run_type(node, env);
}

// 전위 탐색
void search_tree(t_ast *node, t_list *env)
{
    execute_tree(node, env);
    if (node->left != NULL)
        search_tree(node->left, env);
    if (node->right != NULL)
        search_tree(node->right, env);
}
