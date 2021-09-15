
#include "minishell.h"

int syntax_pipeline(t_token_info tokens, int idx, t_ast **node)
{
    *node = new_ast(NULL, AST_PIPE);
    idx = syntax_cmd(tokens, idx, &(*node)->left);
    if (idx == -1)
        return (-1);
    if (tokens.tokens[idx].type == T_PIPE)
        idx = syntax_pipeline(tokens, idx + 1, &(*node)->right);
    return (idx);
}

int syntax_cmd(t_token_info tokens, int idx, t_ast **node)
{
    *node = new_ast(NULL, AST_CMD);

    idx = syntax_simple_cmd(tokens, idx, &(*node)->left);
    if (idx == -1)
        return (-1); // 파싱 실패
    // 다음이 리다이렉션 < << > >> 일경우 , 시도
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        // redirect 은 아직 미구현. idx는 리다이렉션 끝에서 반환.
        idx = syntax_redirects(tokens, idx, &(*node)->right);
        if (idx == -1)
            return (-1);
    }
    return (idx);
}

int syntax_redirects(t_token_info tokens, int idx, t_ast **node)
{
    t_redirect redirect;

    // left, right...
    *node = new_ast(NULL, AST_REDIRECTS);
    idx = syntax_io_redirect(tokens, idx, &(*node)->left);
    if (idx == -1)
        return (-1);
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        idx = syntax_redirects(tokens, idx, &(*node)->right); //계속 들어감...
        if (idx == -1)
            return (-1);
    }
    return (idx);
}

int syntax_io_redirect(t_token_info tokens, int idx, t_ast **node)
{
    t_redirect *redirect;

    // 리다이렉션은 '>' 'file name' 이렇게 왜야함.
    if (tokens.tokens[idx].type == T_REDIRECT && tokens.tokens[idx + 1].type == T_WORD)
    {
        redirect = (t_redirect *)malloc(sizeof(t_redirect));
        if (redirect == NULL)
            allocation_error();
        redirect->type = redirect_type(tokens.tokens[idx].str);
        redirect->filename = ft_strdup(tokens.tokens[idx + 1].str);
        if (redirect->filename == NULL)
            allocation_error();
        *node = new_ast(redirect, AST_REDIRECT); //리다이렉트 저장
    }
    else
        return (-1);
    idx += 2;
    return (idx);
}

int add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx)
{
    int i;

    if (tokens.tokens[idx + 1].type == T_WORD) // 커맨드 다음이 word 일경우
    {
        i = 0;
        while (tokens.tokens[idx + i].type == T_WORD) // 2차원 배열 크기 할당
            i++;
        simple_cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
        if (simple_cmd->argv == NULL)
            allocation_error();
        idx = syntax_argv(tokens, idx, simple_cmd->argv, 0);
    }
    else // 1 command = 1 argv
    {
        simple_cmd->argv = (char **)malloc(sizeof(char *) * (2));
        idx = syntax_argv(tokens, idx, simple_cmd->argv, 0);
    }
    return idx;
}

int syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node)
{
    t_simple_cmd *simple_cmd;

    simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
    if (simple_cmd == NULL)
        allocation_error();
    if (tokens.tokens[idx].type == T_WORD) // cmd name
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

// args 리턴
int syntax_argv(t_token_info tokens, int idx, char **args, int depth)
{
    char *str;

    // tpye이 WORD 일 경우
    if (tokens.tokens[idx].type == T_WORD)
    {
        // 문자열 합치기 args[0] + args[1] ...
        str = ft_strdup(tokens.tokens[idx].str);
        if (str == NULL)
            allocation_error();
        args[depth] = str;
    }
    // <args> WORD
    idx++;
    if (tokens.tokens[idx].type == T_WORD)
        idx = syntax_argv(tokens, idx, args, depth + 1);
    else
        args[depth + 1] = NULL;
    return idx;
}
