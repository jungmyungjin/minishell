/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:16:07 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:16:44 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int		idx;
	char	*key;

	idx = -1;
	if (simple_cmd->argv[1] == NULL)
		return ;
	while (simple_cmd->argv[++idx])
	{
		key = simple_cmd->argv[++idx];
		if (check_env_key(key))
		{
			env_key_error("unset", key);
		}
		else
			unset_env(&env, key);
	}
	global.rtn = 0;
}
