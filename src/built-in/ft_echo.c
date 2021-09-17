//
// Created by 정명진 on 2021/09/16.
//

#include "minishell.h"

/*
 * 결과물 처리 필요
 */

void ft_echo(t_simple_cmd *simple_cmd, t_list *env)
{
	char *contents;
	int idx;

	idx = 0;
	contents = NULL;
	while(simple_cmd->argv[++idx])
	{
		contents = ft_strjoin(contents, ft_strdup(simple_cmd->argv[idx]));
		contents = ft_strjoin(contents, ft_strdup(" "));
	}
	if (contents)
		printf("%s\n", contents);
}
