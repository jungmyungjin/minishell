# include "minishell.h"

int is_redirect(char *str)
{
    if (!ft_strcmp(str, ">"))
        return (1);
    if (!ft_strcmp(str, ">>"))
        return (1);
    if (!ft_strcmp(str, "<"))
        return (1);
    if (!ft_strcmp(str, "<<"))
        return (1);
    return (0);
}

void set_tokenizer_type(t_token_info *token_info)
{
    int i;

    i = 0;
    token_info->tokens[token_info->count].type = T_NULL;
    while (i < token_info->count)
    {
        if (!ft_strcmp(token_info->tokens[i].str, "|"))
            token_info->tokens[i].type = T_PIPE;
        else if (is_redirect(token_info->tokens[i].str))
            token_info->tokens[i].type = T_REDIRECT;
        else
            token_info->tokens[i].type = T_WORD;
        i++;
    }
}

