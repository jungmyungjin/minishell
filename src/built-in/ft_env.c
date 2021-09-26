/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:10:24 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:28:51 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	char	*output;
	char	*line;

	line = NULL;
	output = NULL;
	while (env)
	{
		if (((t_env *)(env->content))->value == NULL)
		{
			env = env->next;
			continue ;
		}
		line = ft_strjoin(ft_strdup(
					((t_env*)(env->content))->origin_text), ft_strdup("\n"));
		output = ft_strjoin(output, line);
		if (line == NULL || output == NULL)
			allocation_error();
		env = env->next;
	}
	write(mcb->fd_output, output, ft_strlen(output));
	free(output);
	g_global.rtn = 0;
	exit(g_global.rtn);
}
