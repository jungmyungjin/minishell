/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:45:23 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 23:59:36 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t dst_len;
	size_t i;

	if (dst == NULL || src == NULL)
		return (0);
	src_len = 0;
	dst_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (src[dst_len] != '\0')
		dst_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && dst_len - i)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
