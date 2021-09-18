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
	int used_newline;

	idx = 0;
	used_newline = 1;
	contents = NULL;
	if (ft_strcmp(simple_cmd->argv[1], "-n") == 0)
	{
		used_newline = 0;
		idx++;
	}
	while(simple_cmd->argv[++idx])
	{
		contents = ft_strjoin(contents, ft_strdup(simple_cmd->argv[idx]));
		contents = ft_strjoin(contents, ft_strdup(" "));
	}
	if (contents)
		write(1, contents, ft_strlen(contents));
	if (used_newline)
		write(1, "\n", 1);
}
