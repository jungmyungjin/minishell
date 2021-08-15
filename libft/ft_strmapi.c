/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:37:09 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*fp)(unsigned int, char))
{
	int		index;
	char	*result;

	result = ft_strdup(s);
	if (!s || !result)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		result[index] = fp(index, s[index]);
		index++;
	}
	return (result);
}
