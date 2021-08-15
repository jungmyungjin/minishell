/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:43:46 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:38 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		idx;
	char	newline;

	if (!s)
		return ;
	idx = 0;
	newline = '\n';
	while (s[idx] != '\0')
	{
		write(fd, &s[idx], 1);
		idx++;
	}
	write(fd, &newline, 1);
}
