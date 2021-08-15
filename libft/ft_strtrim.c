/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:07:18 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set_character(char c, char const *set)
{
	while (set && *set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		len_s1;
	int		idx_start;
	int		idx_end;

	if (!s1)
		return (NULL);
	idx_start = 0;
	idx_end = 0;
	len_s1 = ft_strlen(s1);
	while (is_set_character(s1[idx_start], set))
		idx_start++;
	while ((len_s1 - 1 - idx_end) >= 0 && is_set_character(
			s1[len_s1 - 1 - idx_end], set))
		idx_end++;
	if (len_s1 == idx_start || len_s1 == idx_end)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (len_s1 - idx_start - idx_end + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[idx_start], len_s1 - idx_start - idx_end + 1);
	return (result);
}
