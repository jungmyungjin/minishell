
#include "minishell.h"

char *get_env_value(t_list *env, char *env_key)
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
