/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:21:00 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 07:21:37 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char(char **lines)
{
	int	idx;

	idx = -1;
	while (lines[++idx])
		free(lines[idx]);
	free(lines);
}

char	**get_env_path(t_list *env)
{
	char	*raw_path;
	char	**paths;

	raw_path = get_env_value(env, "PATH");
	paths = ft_split(raw_path, ":");
	free(raw_path);
	return (paths);
}

char	*get_full_path_by_env(t_list *env, char *filename)
{
	struct stat	buf;
	char		**paths;
	char		*tmp;
	char		*full_path;
	int			idx;

	full_path = NULL;
	idx = -1;
	paths = get_env_path(env);
	while (paths[++idx])
	{
		tmp = ft_strjoin(ft_strdup("/"), ft_strdup(filename));
		full_path = ft_strjoin(ft_strdup(paths[idx]), tmp);
		if (stat(full_path, &buf) == -1)
		{
			free(full_path);
			full_path = NULL;
		}
		else
			break ;
	}
	if (paths)
		free_double_char(paths);
	return (full_path);
}
