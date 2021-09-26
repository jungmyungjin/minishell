/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:40:49 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:29:41 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_wpid_status(int status)
{
	g_global.rtn = WEXITSTATUS(status);
	if (WTERMSIG(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_global.rtn = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_global.rtn = 131;
		else
			g_global.rtn = 128 + status;
	}
}

void	set_execve_status(void)
{
	if (errno == EISDIR || errno == EACCES)
	{
		ft_putendl_fd(strerror(EISDIR), STDERR_FILENO);
		exit(126);
	}
	if (errno == ENOENT)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	ft_putendl_fd("command not found", STDERR_FILENO);
	exit(127);
}
