/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:20:52 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:22:27 by mjung            ###   ########.fr       */
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

int	is_env_character(char c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	return (0);
}

int	is_env(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '$')
			return (0);
		if (str[i + 1] == '\0')
			return (0);
		if (ft_isalpha(str[i + 1]))
			return (1);
		if (str[i + 1] == '_')
			return (1);
		if (str[i + 1] == '?')
			return (1);
	}
	return (0);
}
