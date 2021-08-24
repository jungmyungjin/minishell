/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:19:01 by null              #+#    #+#             */
/*   Updated: 2021/08/24 16:30:58 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_delimiter(const char *s, char c)
{
	int	count;
	int	index;
	int	check_delimiter;

	count = 0;
	index = 0;
	check_delimiter = 0;
	while (s[index] != '\0')
	{
		if ((check_delimiter && s[index] != c) || index == 0)
			count++;
		if (s[index] == c)
			check_delimiter = 1;
		else
			check_delimiter = 0;
		index++;
	}
	return (count);
}

static void	free_split_list(char **result)
{
	int	index;

	index = 0;
	while (result[index])
	{
		free(result[index]);
		result[index] = NULL;
		index++;
	}
	free(result);
	result = NULL;
}

static int	string_split(
		char const *s, char delimiter, char **result, int *idx_result)
{
	int	idx_s;
	int	idx_start;

	idx_start = 0;
	idx_s = -1;
	while (s[++idx_s] != '\0')
	{
		if (s[idx_s] == delimiter && s[idx_start] != delimiter)
		{
			result[*idx_result] = ft_substr(
					s, idx_start, idx_s - idx_start + 1);
			if (!result[*idx_result])
				return (1);
			result[(*idx_result)++][idx_s - idx_start] = '\0';
		}
		if (s[idx_s] == delimiter)
			idx_start = idx_s + 1;
	}
	if (!((s[idx_s] == '\0' && s[idx_s - 1] && s[idx_s - 1] != delimiter)
			|| (*idx_result == 0 && idx_start == 0 && s[idx_s] == '\0')))
		return (0);
	result[(*idx_result)++] = ft_substr(s, idx_start, idx_s - idx_start + 1);
	if (!(result[(*idx_result)++]))
		return (1);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		idx_result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_delimiter(s, c) + 1));
	idx_result = 0;
	if (!result)
		return (NULL);
	if (*s != '\0')
		if (string_split(s, c, result, &idx_result) == 1)
			free_split_list(result);
	result[idx_result] = NULL;
	return (result);
}
