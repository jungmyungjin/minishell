/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:09:20 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_tens(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		n *= -1;
	while (n / 10)
	{
		n /= 10;
		count++;
	}
	return (count + 1);
}

static int	squared(int number, int count)
{
	int	result;

	result = 1;
	if (count < 0)
		return (0);
	while (--count)
	{
		result *= number;
	}
	return (result);
}

static void	fill_number(char *result, int n, int idx_result, int len_n)
{
	int	tmp;

	while (len_n > 0)
	{
		tmp = squared(10, len_n);
		result[idx_result] = (n / tmp) + '0';
		n %= tmp;
		idx_result++;
		len_n--;
	}
	result[idx_result] = '\0';
}

char	*ft_itoa(int n)
{
	char	*result;
	int		idx_result;
	int		len_n;
	int		is_nagative;

	idx_result = 0;
	is_nagative = 0;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		is_nagative = 1;
	len_n = count_tens(n);
	result = malloc(sizeof(char) * (len_n + is_nagative + 1));
	if (!result)
		return (NULL);
	if (is_nagative)
	{
		result[idx_result] = '-';
		idx_result++;
		n *= -1;
	}
	fill_number(result, n, idx_result, len_n);
	return (result);
}
