
# include "../../minishell.h"

int is_env_character(char c)
{
    if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
        return (1);
    return (0);
}

// find_env () env list에서 찾아서 있을 경우 치환 그렇지 않으면 공백으로 두기

// token 정보와 token 인덱스를 가지고 할당되어 있는 str을 바꿈.
void change_token(t_token token_info, int token_idx, char *malloc_str)
{
    free(token_info.tokens[token_idx]);
    token_info.tokens[token_idx] = malloc_str;
}

int is_env(char *token, int i)
{
    if (token[i] == '$')
    {
        if (token[i + 1] == '$') // $$ 는 env 가 아님.
            return (0);
        if (token[i + 1] == '\0') // 끝일경우 $만출력  ex) echo $
            return (0);
        if (ft_isalpha(token[i + 1])) // 두번쨰 문자는 알파벳이나 _만 올 수 있음.
            return (1);
        if (token[i + 1] == '_')
            return (1);
    }
    return (0);
}

int is_token_in_env(char *token)
{
    int i;

    i = 0;
    while (token[i] != '\0')
    {
        if(is_env(token, i))
            return (i);
        i++;
    }
    return (-1);
}

int find_dollar_end(char *token, int j)
{
    while (is_env_character(token[j]))
        j++;
    return (j - 1);
}

void set_new_token(char *new_token, char *substr1, char *env_value, char *substr2)
{
    char *sub_ptr1;
    char *sub_ptr2;

    sub_ptr1 = substr1;
    sub_ptr2 = substr2;

    // printf("substr1: %s, env_value: %s, substr2: %s\n", substr1, env_value, substr2);
    while (*substr1 != '\0')
        *(new_token++) = *(substr1++);
    while (*env_value != '\0')
        *(new_token++) = *(env_value++);
    while (*substr2 != '\0')
        *(new_token++) = *(substr2++);
    *new_token = '\0';
    free(sub_ptr1);
    free(sub_ptr2);
}

char *create_new_token(t_list *env, char *token, int start_dollar, int end_dollar) //, char *env_list)
{
    char *env_value;
    char *env_key;
    char *new_token;
    int new_token_len;

    env_key = ft_substr(token, start_dollar + 1, end_dollar - start_dollar); // env key를 문자료열로 만들어서 찾는다.
    // printf("env key: %s", env_key);
    env_value = get_env_value(env, env_key); // env_key 를 사용하여 env_value 가져온다.
    new_token_len = ft_strlen(token) - (end_dollar - start_dollar + 1) + ft_strlen(env_value); // 전체길이 - key길이 + value 길이 // 추후 하나로 합칠 예정. 변수 5개 초과
    new_token = (char *)malloc(sizeof(char) * (new_token_len + 1)); // todo: env 값을 못찾앗을떄 테스트 해봐야함
    if (new_token == NULL)
        allocation_error();
    set_new_token(new_token, ft_substr(token, 0, start_dollar), env_value,
                  ft_substr(token, end_dollar + 1, ft_strlen(token)));
    // printf("new token: %s", new_token);
    free(env_key);
    free(env_value);
    return new_token;
}



void convert_env(t_list *env, t_token token_info)
{
    int i;
    int end_dollar;
    int start_dollar;
    char *new_token;

    i = 0;
    while (i < token_info.token_count)
    {
        start_dollar = is_token_in_env(token_info.tokens[i]);
        if (start_dollar != -1)
        {
            end_dollar = find_dollar_end(token_info.tokens[i], start_dollar + 1);
            new_token = create_new_token(env, token_info.tokens[i], start_dollar, end_dollar);
            free(token_info.tokens[i]);
            token_info.tokens[i] = new_token;
            continue; // 조건에 맞는 env 가 나오지 않을때까지 계속 토큰 반복
        }
        i++;
    }
}

