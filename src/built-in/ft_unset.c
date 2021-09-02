/*
 * 결과물 처리 필요
 */

#include "minishell.h"

void ft_unset(t_list **env_list, char *target_key)
{
	if (check_env_key(target_key))
	{
		env_key_error("unset", target_key);
		return;
	}

	unset_env(env_list, target_key);
}
