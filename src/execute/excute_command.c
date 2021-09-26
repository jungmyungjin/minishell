/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:39:33 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:29:22 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external(t_ast *node, t_list *env, t_mcb *mcb)
{
	extern char	**environ;

	if (execve(((t_simple_cmd *)node->data)->file_path, (
				(t_simple_cmd *)node->data)->argv, environ) == -1)
	{
		set_execve_status();
	}
}

int	execute_set_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	if (!ft_strcmp(simple_cmd->original, "exit"))
	{
		ft_exit(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "unset"))
	{
		ft_unset(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "cd"))
	{
		ft_cd(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "export")
		&& simple_cmd->argv[1] != NULL)
	{
		ft_export(simple_cmd, env, mcb);
		return (1);
	}
	return (0);
}

void	execute_print_built_in(
		t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	if (!ft_strcmp(simple_cmd->original, "env"))
		ft_env(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "export"))
		ft_export(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "pwd"))
		ft_pwd(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "echo"))
		ft_echo(simple_cmd, env, mcb);
}

void	run_using_fork(t_ast *node, t_list *env, t_mcb *mcb)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_external_set_pipe(mcb);
		exec_external_stdout_stdin(mcb);
		if (is_built_in(node->data))
			execute_print_built_in(node->data, env, mcb);
		else
			execute_external(node, env, mcb);
	}
	else if (pid > 0)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		set_wpid_status(status);
		exec_external_close_pipe(mcb);
		exec_external_file_close(mcb);
	}
	else
		ft_putendl_fd("Pid error", STDERR_FILENO);
}

void	execute_command(t_ast *node, t_list *env, t_mcb *mcb)
{
	if (execute_set_built_in(node->data, env, mcb) == 1)
		return ;
	g_global.child = 1;
	run_using_fork(node, env, mcb);
	g_global.child = 0;
}
