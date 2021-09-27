/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:09:13 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:10:20 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	char	*output;
	int		idx;
	int		used_newline;

	idx = 0;
	used_newline = 1;
	output = NULL;
	if (ft_strcmp(simple_cmd->argv[1], "-n") == 0)
	{
		used_newline = 0;
		idx++;
	}
	while (simple_cmd->argv[++idx])
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
	exit(0);
}
