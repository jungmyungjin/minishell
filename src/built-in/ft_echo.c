//
// Created by 정명진 on 2021/09/16.
//

#include "minishell.h"

/*
 * 결과물 처리 필요
 */

void ft_echo(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	char *output;
	int idx;
	int used_newline;

	idx = 0;
	used_newline = 1;
	output = NULL;
	if (ft_strcmp(simple_cmd->argv[1], "-n") == 0)
	{
		used_newline = 0;
		idx++;
	}
	while(simple_cmd->argv[++idx])
	{
		output = ft_strjoin(output, ft_strdup(simple_cmd->argv[idx]));
		output = ft_strjoin(output, ft_strdup(" "));
	}
	if (output != NULL)
	{
		write(mcb->fd_output, output, ft_strlen(output));
		free(output);
	}
	if (used_newline)
		write(mcb->fd_output, "\n", 1);
	global.rtn = 0;
	exit(global.rtn);
}
