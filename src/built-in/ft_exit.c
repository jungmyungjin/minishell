/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:11:49 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:12:05 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (simple_cmd->argv[1] == NULL)
		exit(global.rtn);
	exit_code = ft_atoi(simple_cmd->argv[1]);
	if (ft_strlen(simple_cmd->argv[1]) > 3 || exit_code < 0 || 255 < exit_code)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putendl_fd(
			" : exit: This is not a valid numerical range", STDERR_FILENO);
		exit(255);
	}
	if (simple_cmd->argv[2] != NULL)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putendl_fd(" : exit: too many arguments", STDERR_FILENO);
		global.rtn = 1;
		return ;
	}
	else
		exit(exit_code);
}
