/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:18:21 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_string(const char *big, const char *little, size_t len)
{
	int		big_idx;
	int		little_idx;
	char	*result;

	big_idx = 0;
	little_idx = 0;
	result = (char *)&big[0];
	while (big_idx >= 0 && (unsigned long)big_idx < len && little
		[little_idx] != '\0' && big[big_idx] != '\0')
	{
		if (big[big_idx] == little[little_idx])
		{
			if (little_idx++ == 0)
				result = (char *)&big[big_idx];
		}
		else
		{
			big_idx -= little_idx;
			little_idx = 0;
		}
		big_idx++;
	}
	if (little[little_idx] != '\0')
		result = NULL;
	return (result);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*result;

	if (!big && !little)
		return (NULL);
	result = find_string(big, little, len);
	return (result);
}
