
#include "minishell.h"

t_ast	*new_ast(void *item, int type)
{
    t_ast *new;

    new = malloc(sizeof(t_ast));
    if (new == NULL)
        allocation_error();
    new->left = NULL;
    new->right = NULL;
    new->data = item;
    new->type = type;
    return (new);
}

// 구문 분석
int syntax_analysis(const t_token_info tokens, t_ast **root)
{
    int idx;

    idx = syntax_pipeline(tokens, 0, root);
    if (idx == -1)
    {
        printf("fail to syntax analysis\n");
        return (-1);
    }
    return (0);
}

int syntax_pipeline(t_token_info tokens, int idx, t_ast **node)
{
    *node = new_ast(NULL, AST_PIPE);
    idx = syntax_cmd(tokens, idx, &(*node)->left);
    if (idx == -1)
        return (-1);
    if (tokens.tokens[idx].type == T_PIPE)
    {
        (*node)->right = new_ast(NULL, AST_PIPE);
        idx = syntax_pipeline(tokens, idx + 1, &(*node)->right);
    }
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

int syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node)
{
    int i;
    t_simple_cmd *simple_cmd;

    simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
    if (simple_cmd == NULL)
        allocation_error();
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
            simple_cmd->args = (char **)malloc(sizeof(char *) * (i + 1));
            if (simple_cmd->args == NULL)
                allocation_error();
            idx = syntax_args(tokens, idx, simple_cmd->args, 0);
        }
        else
            simple_cmd->args = NULL; // args가 없음.
        *node = new_ast(simple_cmd, AST_SIMPLE_CMD);
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
    idx++;
    if (tokens.tokens[idx].type == T_WORD)
        idx = syntax_args(tokens, idx, args, depth + 1);
    else
        args[depth + 1] = NULL;
    return idx;
}

