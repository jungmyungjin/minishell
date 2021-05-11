/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:00:50 by mjung             #+#    #+#             */
/*   Updated: 2020/11/14 20:34:22 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	free_string(char **str);
int		ft_strlen(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
void	*ft_memset(void *dest, int c, size_t len);
int		get_next_line(int fd, char **line);

#endif
