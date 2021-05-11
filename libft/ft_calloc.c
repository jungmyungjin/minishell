/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:02:26 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 04:15:31 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, count * size);
	return ((void *)ptr);
}
