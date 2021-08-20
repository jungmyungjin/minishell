# include "../../minishell.h"

// 토큰화하는 함수
char **tokenizer(char *line)
{
    char **tokens;

    tokens = tokenizer_split(line);
    if (tokens == NULL)
        return (NULL);

    // todo: convert env variable in tokens

    // 함수 호출시 전처리가 필요한지 연구 필요
    // todo: convert backslash in tokens

    return tokens;
}

