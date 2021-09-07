
#include "minishell.h"

// 구문 분석
int syntax_analysis(const t_token_info tokens, t_btree *root)
{
    int idx;

    idx = syntax_pipeline(tokens, 0);
    if (idx == -1)
    {
        printf("fail to syntax analysis\n");
        return (-1);
    }
    return (0);
}

int syntax_pipeline(t_token_info tokens, int idx)
{
    idx = syntax_cmd(tokens, idx);
    if (idx == -1)
        return (-1);
    idx++;
    if (tokens.tokens[idx].type == T_PIPE)
        syntax_pipeline(tokens, idx);
    return (idx);
}

int syntax_cmd(t_token_info tokens, int idx)
{
    t_cmd cmd;
    t_simple_cmd *simple_cmd;

    // simple_cmd
    idx = syntax_simple_cmd(tokens, idx, simple_cmd);
    if (idx == -1)
        return (-1); // 파싱 실패
    idx++;
    // 다음이 리다이렉션 < << > >> 일경우 , 시도
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        // redirect 은 아직 미구현. idx는 리다이렉션 끝에서 반환.
        idx = syntax_redirects(tokens, idx);
        if (idx == -1)
            return (-1);
    }
    else
        cmd.redirects = NULL;
    return (idx);
}

int syntax_redirects(t_token_info tokens, int idx)
{

    t_redirect redirect;

    // left, right...
    idx = syntax_io_redirect(tokens, idx);
    if (idx == -1)
        return (-1);
    idx++;
    if (tokens.tokens[idx].type == T_REDIRECT)
    {
        idx = syntax_redirects(tokens, idx); //계속 들어감...
        if (idx == -1)
            return (-1);
    }
    return (idx);
}

int syntax_io_redirect(t_token_info tokens, int idx)
{
    // 리다이렉션은 '>' 'file name' 이렇게 왜야함.
    if (tokens.tokens[idx].type == T_REDIRECT && tokens.tokens[idx + 1].type == T_WORD)
    {
        ;
    }
    else
        return (-1);
    idx += 2;
    return (idx);
}

int syntax_simple_cmd(t_token_info tokens, int idx, t_simple_cmd *simple_cmd)
{
    int i;

    if (tokens.tokens[idx].type == T_WORD) // cmd name
    {
        simple_cmd->cmd_name = ft_strdup(tokens.tokens[idx].str);
        if (simple_cmd->cmd_name == NULL)
            allocation_error();
        idx++;
        if (tokens.tokens[idx].type == T_WORD)
        {
            i = 0;
            while (tokens.tokens[idx + i].type == T_WORD) // 2차원 배열 크기 할당
                i++;
            simple_cmd->args = (char **)malloc(sizeof(char *) * (i));
            if (simple_cmd->args == NULL)
                allocation_error();
            idx = syntax_args(tokens, idx, simple_cmd->args, 0);
        }
        else
            simple_cmd->args = NULL; // args가 없음.
    }
    else
        return (-1);
    return (idx);
}

// args 리턴
int syntax_args(t_token_info tokens, int idx, char **args, int depth)
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
    if (tokens.tokens[idx + 1].type == T_WORD)
    {
        syntax_args(tokens, idx + 1, args, depth + 1);
    }
    return idx;
}

