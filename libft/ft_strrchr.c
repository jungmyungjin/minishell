/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:22:53 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 05:35:02 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p_s;
	char		*p_c;

	p_c = NULL;
	p_s = s;
	while (*p_s != '\0')
	{
		if (*p_s == (char)c)
			p_c = (char *)p_s;
		p_s++;
	}
	if (c == '\0')
		return ((char *)p_s);
	return ((char *)p_c);
}
