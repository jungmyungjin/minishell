/*
 * 결과물 처리 필요
 */

#include "minishell.h"

char *make_export_string(t_list *list_env, char *target_key)
{
	char *line;
	t_env *target_env;

	line = NULL;
	target_env = find_env_by_key(list_env, target_key);
	line = ft_strjoin(line, ft_strdup("declare -x "));
	line = ft_strjoin(line, ft_strdup(target_env->key));
	line = ft_strjoin(line, ft_strdup("=\""));
	line = ft_strjoin(line, ft_strdup(target_env->value));
	line = ft_strjoin(line, ft_strdup("\"\n"));
	return (line);
}

char *found_next_key(t_list *env, char *prev_key)
{
	char *result_key;

	result_key = NULL;
	while (env)
	{
		// 현재 키는 이전키보다 큰키로 셋팅 (첫 셋팅)
		if (result_key == NULL
			&& ft_strcmp(prev_key, ((t_env *)env->content)->key) < 0)
			result_key = ((t_env *)env->content)->key;
		else
		{
			// 이전 키보다는 크고, 이전키를 제외한 다른키중에서는 작은경우
			if (ft_strcmp(prev_key, ((t_env *)env->content)->key) < 0
				&& ft_strcmp(result_key, ((t_env *)env->content)->key) > 0)
				result_key = ((t_env *)env->content)->key;
		}
		env = env->next;
	}
	return (result_key);
}

char *show_env_by_export(t_list *env)
{
	char *prev_key;
	char *current_key;
	char *result;
	int idx;

	idx = -1;
	prev_key = NULL;
	result = NULL;
	while(ft_lstsize(env) > (++idx))
	{
		current_key = found_next_key(env, prev_key);
		result = ft_strjoin(result, make_export_string(env, current_key));
		prev_key = current_key;
	}
	return	(result);
}

// 파이프 및 리다이렉션에 따라 어떻게 리턴할지 달라짐
void ft_export(t_list **env, char *key, char *value)
{
	if (key == NULL)
	{
		// 임시 코드
		printf("%s",show_env_by_export(*env));
		return;
	}
	else if (check_env_key(key))
	{
		env_key_error("export", key);
		return;
	}
	else
		set_env(env, key, value);
}

