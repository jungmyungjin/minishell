/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:01:54 by mjung             #+#    #+#             */
/*   Updated: 2020/11/14 20:31:15 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *s1)
{
	int count;

	count = 0;
	if (s1 == NULL)
		return (0);
	while (s1[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		total_size;
	int		idx_total;
	int		idx_tmp;

	if (!s1 && !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2);
	if (!(result = (char*)malloc(sizeof(char) * (total_size + 1))))
		return (NULL);
	idx_total = 0;
	idx_tmp = 0;
	if (s1)
		while ((char)s1[idx_tmp] != '\0')
			result[idx_total++] = s1[idx_tmp++];
	idx_tmp = 0;
	if (s2)
		while ((char)s2[idx_tmp] != '\0')
			result[idx_total++] = s2[idx_tmp++];
	free(s1);
	free(s2);
	result[idx_total] = '\0';
	return (result);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		length;
	int		index;

	index = 0;
	length = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	while (index < length)
	{
		new[index] = ((char*)s1)[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}

void	*ft_memset(void *dest, int c, size_t len)
{
	int		index;
	char	*local_dest;

	if (!dest)
		return (dest);
	index = 0;
	local_dest = (char *)dest;
	while ((unsigned long)index < len)
	{
		local_dest[index] = c;
		index++;
	}
	return (local_dest);
}

void	free_string(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}
