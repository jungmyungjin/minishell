#include "minishell.h"

/*
 * 결과물 처리 필요
 */

void ft_env(t_list *env)
{
	char *result;
	char *line;

	line = NULL;
	result = NULL;
	while(env)
	{
		line = ft_strjoin(ft_strdup(((t_env*)(env->content))->origin_text), ft_strdup("\n"));
		result = ft_strjoin(result, line);
		if (line == NULL || result == NULL)
			allocation_error();
		env = env->next;
	}
	printf("%s", result);
}
