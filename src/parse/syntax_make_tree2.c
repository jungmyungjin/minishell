#include "minishell.h"

t_ast	*new_ast(void *item, int type)
{
    t_ast *new;

    new = (t_ast *)malloc(sizeof(t_ast));
    if (new == NULL)
        allocation_error();
    new->left = NULL;
    new->right = NULL;
    new->data = item;
    new->type = type;
    return (new);
}

int redirect_type(char *str)
{
    if (!ft_strcmp(str, "<"))
        return INPUT;
    if (!ft_strcmp(str, ">"))
        return OUTPUT;
    if (!ft_strcmp(str, "<<"))
        return HERE_DOCUMENTS;
    if (!ft_strcmp(str, ">>"))
        return APPENDING_OUTPUT;
    return (0);
}
