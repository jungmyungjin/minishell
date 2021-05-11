/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:30:41 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 04:55:35 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	const char *p_s;

	p_s = s;
	while (*p_s != '\0')
	{
		if (*p_s == (char)c)
			return ((char *)p_s);
		p_s++;
	}
	if (c == '\0')
		return ((char *)p_s);
	return (NULL);
}
