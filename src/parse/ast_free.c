
#include "minishell.h"

void free_simple_cmd(t_simple_cmd *simple_cmd)
{
    int i;

    i = 0;
    free(simple_cmd->cmd_name);
    if (simple_cmd->args == NULL)
        return ;
    while (simple_cmd->args[i] != NULL)
    {
        free(simple_cmd->args[i]);
        i++;
    }
    free(simple_cmd->args);
}

void free_redirect(t_redirect *redirect)
{
    free(redirect->filename);
}

void free_ast_node(t_ast **node)
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

void free_tree(t_ast **node)
{
    if ((*node)->left != NULL)
        free_tree(&(*node)->left);
    if ((*node)->right != NULL)
        free_tree(&(*node)->right);
    free_ast_node(node);
    free(*node);
}