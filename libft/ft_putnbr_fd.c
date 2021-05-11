/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 04:30:20 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/02 05:02:15 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	nbr(unsigned int num, int fd)
{
	unsigned int	quotient;
	unsigned int	remainder;
	char			*base;

	base = "0123456789";
	if (num < 10)
	{
		ft_putchar_fd(base[num], fd);
		return ;
	}
	quotient = num / 10;
	remainder = num % 10;
	nbr(quotient, fd);
	ft_putchar_fd(base[remainder], fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr((unsigned int)(n * -1), fd);
	}
	else
		nbr((unsigned int)(n), fd);
}
