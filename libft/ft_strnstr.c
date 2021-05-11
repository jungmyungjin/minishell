/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:03:43 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 02:34:40 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i <= len - needle_len && *haystack != '\0')
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char*)haystack);
		i++;
		haystack++;
	}
	return (NULL);
}
