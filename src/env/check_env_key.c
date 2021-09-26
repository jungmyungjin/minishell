/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:19:57 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:20:58 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	allowed_character(char *string)
{
	int	idx;

	idx = -1;
	if ('0' <= string[0] && string[0] <= '9')
		return (0);
	while (string[++idx])
	{
		if (!(('a' <= string[idx] && string[idx] <= 'z')
				|| ('A' <= string[idx] && string[idx] <= 'Z')
				|| ('0' <= string[idx] && string[idx] <= '9')
				|| '_' == string[idx]))
		{
			return (0);
		}
	}
	return (1);
}

int	check_env_key(char *key)
{
	if (ft_strcmp(key, "$?") == 0)
		return (1);
	if (allowed_character(key))
		return (0);
	return (1);
}
