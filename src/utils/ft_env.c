#include "../../minishell.h"

/*
 * return 으로 메모리가 할당되어있는 char 배열을 반환함. 호출한 함수에서 free필수!
 *  메모리 할당 실패시 error exit
 */
char *get_env_value(char *env_key)
{
    char *env_value = "test";
    char *result;

    if (!ft_strcmp(env_key, env_value))
        result = ft_strdup("env_value123");
    else
        result = ft_strdup(""); //  env value 에서는 비어있는 값을 리턴해야함.
    if (result == NULL)  // 메모리 할당 실패
        allocation_error();
    return result;
}
