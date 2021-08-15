/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:03:03 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	int		srclen;

	index = 0;
	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize > 0)
	{
		while (index < (dstsize - 1) && src[index] != '\0')
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (srclen);
}
