/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:22:46 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:31:45 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envnew(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->origin_text = NULL;
	new->key = NULL;
	new->value = NULL;
	return (new);
}

void	set_env_key_value(char *origin_text, char **key, char **value)
{
	int	idx;

	idx = 0;
	while (origin_text[idx])
	{
		if (origin_text[idx] == '=')
			break ;
		idx++;
	}
	*key = ft_substr(origin_text, 0, idx);
	*value = ft_substr(origin_text, idx + 1, ft_strlen(origin_text) - idx);
	if (*key == NULL || *value == NULL)
		allocation_error();
}

void	env_initialize(t_list **env, char **envp)
{
	t_list	*env_data;
	t_env	*new_env;
	t_list	*new_list;

	env_data = NULL;
	while (*envp)
	{
		new_env = envnew();
		new_list = ft_lstnew(new_env);
		if (new_env == NULL || new_list == NULL)
			allocation_error();
		new_env->origin_text = ft_strdup(*envp);
		if (new_env->origin_text == NULL)
			allocation_error();
		set_env_key_value(
			new_env -> origin_text, &(new_env->key), &(new_env->value));
		ft_lstadd_back(&env_data, new_list);
		envp++;
	}
	*(env) = env_data;
}
