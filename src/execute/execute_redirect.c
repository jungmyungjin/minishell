/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:40:47 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 06:41:41 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char *filename, t_mcb *mcb)
{
	if (mcb->fd_output != STDOUT_FILENO)
		close(mcb->fd_output);
	mcb->fd_output = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void	redirect_append(char *filename, t_mcb *mcb)
{
	if (mcb->fd_output != STDOUT_FILENO)
		close(mcb->fd_output);
	mcb->fd_output = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
}

void	redirect_input(char *filename, t_mcb *mcb)
{
	int	file_open;

	file_open = open(filename, O_RDONLY);
	if (file_open < 0)
	{
		ft_putendl_fd("FILE OPEN INPUT ERROR", STDERR_FILENO);
		global.rtn = 1;
	}
	else
	{
		if (mcb->fd_input != STDIN_FILENO)
			close(mcb->fd_input);
		mcb->fd_input = file_open;
	}
}

void	redirect_heredoc(char *eof_keyword, t_mcb *mcb)
{
	char	*line;
	int		fd[2];
	int		status;

	status = pipe(fd);
	if (status < 0)
		exit(0);
	if (mcb->fd_input != STDIN_FILENO)
		close(mcb->fd_input);
	while (1)
	{
		line = readline("> ");
		if (!strcmp(line, eof_keyword))
		{
			free(line);
			break ;
		}
		write(fd[WRITE_END], line, ft_strlen(line));
		write(fd[WRITE_END], "\n", 1);
		free(line);
	}
	close(fd[WRITE_END]);
	mcb->fd_input = fd[READ_END];
}

void	execute_redirect(t_redirect *redirect, t_mcb *mcb)
{
	if (redirect->type == OUTPUT)
		redirect_output(redirect->filename, mcb);
	else if (redirect->type == INPUT)
		redirect_input(redirect->filename, mcb);
	else if (redirect->type == HERE_DOCUMENTS)
		redirect_heredoc(redirect->filename, mcb);
	else if (redirect->type == APPENDING_OUTPUT)
		redirect_append(redirect->filename, mcb);
	if (mcb->fd_output < 0)
	{
		ft_putendl_fd("FILE OPEN OUTPUT ERROR", STDERR_FILENO);
		exit(1);
	}
}
