/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:27:14 by mjung             #+#    #+#             */
/*   Updated: 2021/08/27 01:03:50 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	do_join(char **s, char **result, int *idx_total)
{
	int	idx_tmp;

	idx_tmp = 0;
	if (*s)
	{
		while ((char)((*s)[idx_tmp]) != '\0')
			((*result)[(*idx_total)++]) = ((*s)[idx_tmp++]);
		free(*s);
		*s = NULL;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		total_size;
	int		idx_total;

	if (!s1 && !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (total_size + 1));
	if (!result)
		return (NULL);
	idx_total = 0;
	if (s1)
		do_join(&s1, &result, &idx_total);
	if (s2)
		do_join(&s2, &result, &idx_total);
	result[idx_total] = '\0';
	return (result);
}
