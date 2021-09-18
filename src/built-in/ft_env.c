#include "minishell.h"

/*
 * 결과물 처리 필요
 */

void ft_env(t_simple_cmd *simple_cmd, t_list *env)
{
	char *result;
	char *line;

	line = NULL;
	result = NULL;
	while(env)
	{
		if (((t_env*)(env->content))->value == NULL)
		{
			env = env->next;
			continue;
		}
		line = ft_strjoin(ft_strdup(((t_env*)(env->content))->origin_text), ft_strdup("\n"));
		result = ft_strjoin(result, line);
		if (line == NULL || result == NULL)
			allocation_error();
		env = env->next;
	}
	write(1, result, ft_strlen(result));
}
