/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:52:40 by ychoi             #+#    #+#             */
/*   Updated: 2020/12/30 16:47:20 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t			dst_len;
	size_t			src_len;
	size_t			copy_len;
	char			*p_src;

	dst_len = 0;
	src_len = 0;
	p_src = src;
	while (*(src++) != '\0')
		src_len++;
	while (*(dst++) != '\0')
		dst_len++;
	dst--;
	copy_len = size - dst_len - 1;
	if (size <= dst_len)
		return (src_len + size);
	while (copy_len && *p_src != '\0')
	{
		*(dst++) = *(p_src++);
		copy_len--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
