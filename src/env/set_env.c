/*
 * 결과물 처리 필요
 */

#include "minishell.h"

void set_env(t_list **env, char *key, char *value)
{
	t_list	*new_list;
	t_env	*new_contets;
	char	*origin_text;

	new_contets = envnew();
	new_list = ft_lstnew(new_contets);

	if (value)
	{
		origin_text = ft_strjoin(ft_strdup(key), ft_strdup("="));
		origin_text = ft_strjoin(origin_text, ft_strdup(value));
	}
	else
		origin_text = ft_strdup(key);

	if (new_list == NULL || origin_text == NULL || new_contets == NULL)
		allocation_error();

	new_contets->origin_text = origin_text;
	new_contets->key = ft_strdup(key);
	if (value)
		new_contets->value = ft_strdup(value);
	ft_lstadd_back(env, new_list);
}