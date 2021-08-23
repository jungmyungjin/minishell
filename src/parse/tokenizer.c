# include "../../minishell.h"

void convert_env(t_token token);

int find_dollar(char *string);


// 토큰화하는 함수
char **tokenizer(char *line)
{
    t_token token_info;

    token_info = tokenizer_split(line);
    if (token_info.token_count == 0) // line 이 null일 경우
        return (NULL);

    // convert env variable in tokens
    convert_env(token_info);
    //for (int i = 0; i < token_info.token_count; i++)
    //    printf("[%d] %s\n", i, token_info.tokens[i]);

    // 함수 호출시 전처리가 필요한지 연구 필요
    // todo: convert backslash in tokens

    return token_info.tokens;
}

