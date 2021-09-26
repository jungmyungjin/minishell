/*
 * 결과물 처리 필요
 */

#include "minishell.h"

void set_env_value(t_env *env, char *key, char *value)
{
	char	*origin_text;

	if (value)
	{
		origin_text = ft_strjoin(ft_strdup(key), ft_strdup("="));
		origin_text = ft_strjoin(origin_text, ft_strdup(value));
	}
	else
		origin_text = ft_strdup(key);

	if (origin_text == NULL)
		allocation_error();
	env->origin_text = origin_text;
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
}

void set_new_env(t_list **env, char *key, char *value)
{
	t_list	*new_list;
	t_env	*new_contets;
	char	*origin_text;

	new_contets = envnew();
	new_list = ft_lstnew(new_contets);
	if (new_list == NULL || origin_text == NULL || new_contets == NULL)
		allocation_error();
	set_env_value(new_contets, key, value);
	ft_lstadd_back(env, new_list);
}

void set_env(t_list **env, char *key, char *value)
{
	t_env *set_target;

	set_target = find_env_by_key(*env, key);
	if (set_target == NULL)
		set_new_env(env, key, value);
	else if (value != NULL)
	{
		free(set_target->origin_text);
		free(set_target->key);
		if (set_target->value != NULL)
			free(set_target->value);
		set_env_value(set_target, key, value);
	}
}
