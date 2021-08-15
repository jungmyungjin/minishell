/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:11:31 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:38 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		index;
	char	*target;

	index = 0;
	target = NULL;
	while (s[index] != '\0')
	{
		if (s[index] == c)
		{
			target = &s[index];
			break ;
		}
		index++;
	}
	if (s[index] == '\0' && s[index] == c)
		target = &s[index];
	return (target);
}
