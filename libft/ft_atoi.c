/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:54:10 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 23:20:24 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_space(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int		is_over_min_int(long long num, int sign)
{
	if (sign == -1 && num * sign < INT_MIN)
		return (1);
	return (0);
}

int		is_over_max_int(long long num, int sign)
{
	if (sign == 1 && INT_MAX < num * sign)
		return (1);
	return (0);
}

int		ft_atoi(const char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
		if (is_over_max_int(num, sign))
			return (-1);
		if (is_over_min_int(num, sign))
			return (0);
	}
	return (sign * num);
}
