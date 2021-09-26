/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:43:06 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 06:43:11 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	if (!ft_strcmp(simple_cmd->original, "cd"))
		ft_cd(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "env"))
		ft_env(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "export"))
		ft_export(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "unset"))
		ft_unset(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "pwd"))
		ft_pwd(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "echo"))
		ft_echo(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "exit"))
		ft_exit(simple_cmd, env, mcb);
}
