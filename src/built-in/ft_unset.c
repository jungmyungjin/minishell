/*
 * 결과물 처리 필요
 */

#include "minishell.h"

void ft_unset(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int idx;
	char *key;

	idx = -1;
	if (simple_cmd->argv[1] == NULL)
		return;
	while(simple_cmd->argv[++idx])
	{
		key = simple_cmd->argv[++idx];
		if (check_env_key(key))
		{
			env_key_error("unset", key);
		}
		else
			unset_env(&env, key);
	}
	global.rtn = 0;
	exit(global.rtn);
}
