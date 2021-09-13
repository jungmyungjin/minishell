#include "minishell.h"

int syntax_pipeline_check(t_token_info tokens, int idx)
{
    idx = syntax_cmd_check(tokens, idx);
    if (idx == -1)
        return (-1);
    if (tokens.tokens[idx].type == T_PIPE)
        idx = syntax_pipeline_check(tokens, idx + 1);
    return (idx);
}

int syntax_cmd_check(t_token_info tokens, int idx)
{
    idx = syntax_simple_cmd_check(tokens, idx);
    if (idx == -1)
        return (-1); // 파싱 실패
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        idx = syntax_redirects_check(tokens, idx);
        if (idx == -1)
            return (-1);
    }
    return (idx);
}

int syntax_redirects_check(t_token_info tokens, int idx)
{
    idx = syntax_io_redirect_check(tokens, idx);
    if (idx == -1)
        return (-1);
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        idx = syntax_redirects_check(tokens, idx);
        if (idx == -1)
            return (-1);
    }
    return (idx);
}

int syntax_io_redirect_check(t_token_info tokens, int idx)
{
    if (tokens.tokens[idx].type == T_REDIRECT && tokens.tokens[idx + 1].type == T_WORD)
        ;
    else
        return (-1);
    idx += 2;
    return (idx);
}

int syntax_simple_cmd_check(t_token_info tokens, int idx)
{
    int i;

    if (tokens.tokens[idx].type == T_WORD) // cmd name
    {
        idx++;
        if (tokens.tokens[idx].type == T_WORD)
        {
            i = 0;
            while (tokens.tokens[idx + i].type == T_WORD)
                i++;
            idx += i;
        }
    }
    else
        return (-1);
    return (idx);
}
