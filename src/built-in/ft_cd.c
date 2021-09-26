/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:08:42 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:09:09 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int		rtn;
	char	*output;

	rtn = chdir(simple_cmd->argv[1]);
	output = ft_strjoin(ft_strdup(strerror(errno)), ft_strdup("\n"));
	if (rtn == -1)
		write(2, output, ft_strlen(output) + 1);
	if (output)
		free(output);
	global.rtn = 0;
}
