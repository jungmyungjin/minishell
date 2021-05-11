/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:47:33 by ychoi             #+#    #+#             */
/*   Updated: 2020/12/31 17:09:04 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p_b;

	p_b = b;
	i = 0;
	while (i < len)
	{
		p_b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
