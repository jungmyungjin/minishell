
# include "minishell.h"

int is_env_character(char c)
{
    if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
        return (1);
    return (0);
}

// find_env () env list에서 찾아서 있을 경우 치환 그렇지 않으면 공백으로 두기

int is_env(char *str, int i)
{
    if (str[i] == '$')
    {
        if (str[i + 1] == '$') // $$ 는 env 가 아님.
            return (0);
        if (str[i + 1] == '\0') // 끝일경우 $만출력  ex) echo $
            return (0);
        if (ft_isalpha(str[i + 1])) // 두번쨰 문자는 알파벳이나 _만 올 수 있음.
            return (1);
        if (str[i + 1] == '_')
            return (1);
    }
    return (0);
}

int is_token_in_env(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if(is_env(str, i))
            return (i);
        i++;
    }
    return (-1);
}

int find_dollar_end(char *str, int j)
{
    while (is_env_character(str[j]))
        j++;
    return (j - 1);
}

void set_new_str(char *new_str, char *substr1, char *env_value, char *substr2)
{
    char *sub_ptr1;
    char *sub_ptr2;

    sub_ptr1 = substr1;
    sub_ptr2 = substr2;

    // printf("substr1: %s, env_value: %s, substr2: %s\n", substr1, env_value, substr2);
    while (*substr1 != '\0')
        *(new_str++) = *(substr1++);
    while (*env_value != '\0')
        *(new_str++) = *(env_value++);
    while (*substr2 != '\0')
        *(new_str++) = *(substr2++);
    *new_str = '\0';
    free(sub_ptr1);
    free(sub_ptr2);
}

char *create_new_str(t_list *env, char *token, int start_dollar, int end_dollar) //, char *env_list)
{
    char *env_value;
    char *env_key;
    char *new_str;
    int new_str_len;

    env_key = ft_substr(token, start_dollar + 1, end_dollar - start_dollar); // env key를 문자료열로 만들어서 찾는다.
    // printf("env key: %s", env_key);
    env_value = get_env_value(env, env_key); // env_key 를 사용하여 env_value 가져온다.
    new_str_len = ft_strlen(token) - (end_dollar - start_dollar + 1) + ft_strlen(env_value); // 전체길이 - key길이 + value 길이 // 추후 하나로 합칠 예정. 변수 5개 초과
    new_str = (char *)malloc(sizeof(char) * (new_str_len + 1)); // todo: env 값을 못찾앗을떄 테스트 해봐야함
    if (new_str == NULL)
        allocation_error();
    set_new_str(new_str, ft_substr(token, 0, start_dollar), env_value,
                  ft_substr(token, end_dollar + 1, ft_strlen(token)));
    // printf("new token: %s", new_str);
    free(env_key);
    free(env_value);
    return new_str;
}



void convert_env(t_list *env, t_token_info *token_info)
{
    int i;
    int end_dollar;
    int start_dollar;
    char *new_str;

    i = 0;
    while (i < token_info->count)
    {
        if (token_info->tokens[i].type != T_SINGLE_QUOTES)
        {
            start_dollar = is_token_in_env(token_info->tokens[i].str);
            if (start_dollar != -1)
            {
                end_dollar = find_dollar_end(token_info->tokens[i].str, start_dollar + 1);
                new_str = create_new_str(env, token_info->tokens[i].str, start_dollar, end_dollar);
                free(token_info->tokens[i].str);
                token_info->tokens[i].str = new_str;
                continue; // 조건에 맞는 env 가 나오지 않을때까지 계속 토큰 반복
            }
        }
        i++;
    }
}
