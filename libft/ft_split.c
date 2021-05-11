/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:41:04 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 05:48:21 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	counting_words(char const *s, char c)
{
	size_t count;

	count = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != '\0' && *s != c)
				s++;
			count++;
		}
	}
	return (count);
}

void	*free_split(char **ptr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**split_by_words(char const *s, char c, char **d, size_t row_count)
{
	size_t row;
	size_t col;

	row = 0;
	while (*s != '\0' && row < row_count)
	{
		if (*s == c)
			s++;
		else
		{
			col = 0;
			while (*s != '\0' && *s != c)
			{
				col++;
				s++;
			}
			d[row] = (char *)malloc(sizeof(char) * (col + 1));
			if (d[row] == NULL)
				return (free_split(d, row_count + 1));
			ft_strlcpy(d[row], s - col, col + 1);
			row++;
		}
	}
	row_count[d] = NULL;
	return (d);
}

char	**ft_split(char const *s, char c)
{
	char	**d;
	size_t	row_count;

	if (s == NULL)
		return (NULL);
	row_count = counting_words(s, c);
	d = (char **)malloc(sizeof(char *) * (row_count + 1));
	if (d == NULL)
		return (NULL);
	return (split_by_words(s, c, d, row_count));
}
