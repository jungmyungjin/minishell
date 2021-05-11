/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 05:16:52 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/08 10:00:51 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		int_len(int n)
{
	size_t len;

	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*dst;
	size_t	len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = int_len(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	dst[len--] = '\0';
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
	}
	while (n != 0)
	{
		dst[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (dst);
}
