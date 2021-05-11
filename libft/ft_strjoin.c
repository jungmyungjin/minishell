/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:37:21 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 10:01:16 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s;
	char	*p_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (s == NULL)
		return (NULL);
	p_s = ft_memccpy(s, s1, '\0', s1_len + 1);
	ft_strlcat(p_s - 1, (char *)s2, s2_len + 1);
	return (s);
}
