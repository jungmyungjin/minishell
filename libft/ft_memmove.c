/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:01:11 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 02:52:56 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	if (dst == '\0' && src == '\0')
		return (NULL);
	i = 0;
	p_dst = dst;
	p_src = src;
	while (i < len)
	{
		if (dst <= src)
			p_dst[i] = p_src[i];
		else
			p_dst[len - i - 1] = p_src[len - i - 1];
		i++;
	}
	return (dst);
}
