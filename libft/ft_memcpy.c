/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:32:52 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 03:58:05 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p_dst;
	const unsigned char *p_src;
	size_t				i;

	i = 0;
	if (dst == '\0' && src == '\0')
		return (NULL);
	p_dst = dst;
	p_src = src;
	while (i < n)
	{
		*(p_dst++) = *(p_src++);
		i++;
	}
	return (dst);
}
