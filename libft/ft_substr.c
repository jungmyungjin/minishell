/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 20:09:10 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 10:01:46 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *d;

	if (s == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (ft_strlen(s) <= start)
	{
		*d = '\0';
		return (d);
	}
	s += start;
	ft_strlcpy(d, s, len + 1);
	return (d);
}
