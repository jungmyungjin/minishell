/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:25:45 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:31:13 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_list **target)
{
	free(((t_env *)((*target)->content))->origin_text);
	free(((t_env *)((*target)->content))->key);
	if (((t_env *)((*target)->content))->value != NULL)
		free(((t_env *)((*target)->content))->value);
	free(((*target)->content));
	(*target)->next = NULL;
	free(*target);
}

void	delete_list_by_key(t_list **all_list, t_list *prev, t_list *current)
{
	if (prev == NULL)
	{
		*all_list = current->next;
		free_env_list(&current);
	}
	else if (current->next == NULL)
	{
		prev->next = NULL;
		free_env_list(&current);
	}
	else
	{
		prev->next = current->next;
		free_env_list(&current);
	}
}

void	unset_env(t_list **env_list, char *target_key)
{
	t_list	*my_list;
	t_list	*prev_list;

	my_list = *env_list;
	prev_list = NULL;
	while (my_list)
	{
		if (ft_strcmp(((t_env *)((my_list)->content))->key, target_key) == 0)
		{
			delete_list_by_key(env_list, prev_list, my_list);
			break ;
		}
		prev_list = my_list;
		my_list = my_list->next;
	}
}
