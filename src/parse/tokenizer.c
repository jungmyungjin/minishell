# include "../../minishell.h"

// 토큰화하는 함수
int lexical_analysis(t_list *env, char *line, t_token_info *token_info)
{
    int result;

    // 문자열 분리 ["ls", "-al", "|", "cat"]
    result = tokenizer_split(line, token_info);
    if (result == -1) // line 이 null일 경우
        return (-1);

    // convert env variable in tokens
    convert_env(env, token_info);

    // 함수 호출시 전처리가 필요한지 연구 필요
    // todo: convert backslash in tokens

    // token 에 의미(type) 부여
    set_tokenizer_type(token_info);

//    for (int i = 0; i < token_info->count; i++)
//        printf("[%d] %s\n", i, token_info->tokens[i].str);


    return (0);
}

