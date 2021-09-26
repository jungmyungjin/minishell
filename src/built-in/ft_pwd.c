/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:15:48 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:29:12 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	return (current_path);
}

void	ft_pwd(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	char	*output;

	output = getcwd(NULL, 0);
	output = ft_strjoin(output, ft_strdup("\n"));
	write(mcb->fd_output, output, ft_strlen(output));
	free(output);
	g_global.rtn = 0;
	exit(g_global.rtn);
}
