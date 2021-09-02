#include "minishell.h"

char *find_value_by_key(t_list *env, char *env_key)
{
	char *result;
	t_list *my_env;

	result = NULL;
	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_env*)my_env->content)->key, env_key) == 0)
		{
			result = ft_strdup(((t_env*)my_env->content)->value);
			if (result == NULL)
				allocation_error();
			break;
		}
		my_env = my_env->next;
	}
	if (result == NULL)
		result = ft_strdup("");
	if (result == NULL)
		allocation_error();
	return result;
}

char *get_env_value(t_list *env, char *env_key)
{
	char *result;

	// 특수변수 예외처리
	if (ft_strcmp(env_key, "$?"))
	{
		// 면령어 결과값을 찾는 로직 추가
		// 이전명령어의 결과값 출력
	}

	result = find_value_by_key(env, env_key);

	return result;
}
