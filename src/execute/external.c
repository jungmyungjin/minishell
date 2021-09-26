/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:32:33 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:41:06 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external_set_pipe(t_mcb *mcb)
{
	if (mcb->pre_pipe_check == 1)
	{
		if (mcb->pipe_read_end != STDIN_FILENO)
		{
			dup2(mcb->pipe_read_end, STDIN_FILENO);
			close(mcb->pipe_read_end);
		}
	}
	if (mcb->next_pipe_check == 1)
	{
		close(mcb->fd[READ_END]);
		dup2(mcb->pipe_write_end, STDOUT_FILENO);
		close(mcb->pipe_write_end);
	}
}

void	exec_external_file_close(t_mcb *mcb)
{
	if (mcb->fd_input != STDIN_FILENO)
		close(mcb->fd_input);
	if (mcb->fd_output != STDOUT_FILENO)
		close(mcb->fd_output);
}

void	exec_external_stdout_stdin(t_mcb *mcb)
{
	if (mcb->fd_input != STDIN_FILENO)
		dup2(mcb->fd_input, STDIN_FILENO);
	if (mcb->fd_output != STDOUT_FILENO)
		dup2(mcb->fd_output, STDOUT_FILENO);
}

void	exec_external_close_pipe(t_mcb *mcb)
{
	if (mcb->pre_pipe_check == 1)
	{
		close(mcb->pipe_read_end);
		mcb->pre_pipe_check = 0;
	}
	if (mcb->next_pipe_check == 1)
	{
		close(mcb->fd[WRITE_END]);
		mcb->next_pipe_check = 0;
		mcb->pipe_read_end = mcb->fd[READ_END];
		mcb->pre_pipe_check = 1;
	}
}
