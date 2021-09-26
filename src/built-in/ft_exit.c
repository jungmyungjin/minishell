//
// Created by 정명진 on 2021/09/16.
//


#include "minishell.h"

/*
 * 결과물 처리 필요
 */

void ft_exit(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (simple_cmd->argv[1] == NULL)
		exit(global.rtn);
	exit_code = ft_atoi(simple_cmd->argv[1]);
	if (ft_strlen(simple_cmd->argv[1]) > 3 || exit_code < 0 || 255 < exit_code)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putendl_fd(" : exit: This is not a valid numerical range", STDERR_FILENO);
		exit(255);
	}
	if (simple_cmd->argv[2] != NULL)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putendl_fd(" : exit: too many arguments", STDERR_FILENO);
		global.rtn = 1;
		return;
	}
	else
		exit(exit_code);
}
