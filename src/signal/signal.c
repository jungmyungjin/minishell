/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:38:53 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 06:39:49 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_new_line(int status)
{
	global.rtn = 130;
	if (global.child == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_exit_shell(void)
{
	printf("bye\n");
	exit(EXIT_SUCCESS);
}

void	set_signal(void)
{
	signal(SIGINT, sig_new_line);
	signal(SIGQUIT, SIG_IGN);
}
