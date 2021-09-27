/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:22:00 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:22:43 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_by_key(t_list *env, char *env_key)
{
	t_list	*my_env;

	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_env *)my_env->content)->key, env_key) == 0)
			return (my_env->content);
		my_env = my_env->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env, char *env_key)
{
	char	*result;
	t_env	*found_env;

	found_env = find_env_by_key(env, env_key);
	if (found_env == NULL)
		result = ft_strdup("");
	else
		result = ft_strdup(found_env->value);
	if (result == NULL)
		allocation_error();
	return (result);
}
