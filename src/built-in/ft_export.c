/*
 * 결과물 처리 필요
 */

#include "minishell.h"

void ft_export(t_list **env, char *key, char *value)
{
	if (check_env_key(key))
	{
		env_key_error("export", key);
		return;
	}

	set_env(env, key, value);
}

