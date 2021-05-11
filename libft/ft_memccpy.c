/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:31:53 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 03:58:52 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*p_dst;
	const unsigned char		*p_src;
	size_t					i;

	i = 0;
	p_dst = dst;
	p_src = src;
	while (i < n)
	{
		*p_dst = *p_src;
		if (*p_dst == (unsigned char)c)
			return (p_dst + 1);
		p_src++;
		p_dst++;
		i++;
	}
	return (NULL);
}
