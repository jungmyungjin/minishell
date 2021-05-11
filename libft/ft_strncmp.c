/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:12:57 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 05:22:04 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char *p_s1;
	const unsigned char *p_s2;
	size_t				i;

	i = 0;
	if (n == 0)
		return (0);
	p_s1 = (const unsigned char *)s1;
	p_s2 = (const unsigned char *)s2;
	while (i < (n - 1) && *p_s1 != '\0' && *p_s2 != '\0')
	{
		if (*p_s1 != *p_s2)
			break ;
		i++;
		p_s1++;
		p_s2++;
	}
	return (*p_s1 - *p_s2);
}
