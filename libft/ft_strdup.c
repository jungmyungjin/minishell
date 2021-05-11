/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:07:08 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 10:01:04 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*d1;

	d1 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (d1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		d1[i] = s1[i];
		i++;
	}
	d1[i] = '\0';
	return (d1);
}
