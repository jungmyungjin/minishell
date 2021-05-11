/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:33:46 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 10:01:40 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*d1;
	size_t	start_idx;
	size_t	end_idx;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start_idx = 0;
	end_idx = ft_strlen(s1) - 1;
	while (s1[start_idx] != '\0' && ft_strchr(set, s1[start_idx]) != '\0')
		start_idx++;
	while (s1[end_idx] != '\0' && ft_strchr(set, s1[end_idx]) != '\0' &&
			1 < end_idx)
		end_idx--;
	if (end_idx <= start_idx)
		return (ft_strdup(""));
	d1 = (char *)malloc(sizeof(char) * (end_idx - start_idx + 2));
	ft_strlcpy(d1, &s1[start_idx], end_idx - start_idx + 2);
	return (d1);
}
