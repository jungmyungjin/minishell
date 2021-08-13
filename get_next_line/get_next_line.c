/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:00:39 by mjung             #+#    #+#             */
/*   Updated: 2020/11/14 20:28:30 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(int fd, char **buffer)
{
	int		result;

	result = 0;
	*buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_memset(*buffer, '\0', BUFFER_SIZE + 1);
	result = read(fd, *buffer, BUFFER_SIZE);
	return (result);
}

static int	read_more(char **buffer, int fd, char **new_line)
{
	int result;

	*new_line = ft_strjoin(*new_line, *buffer);
	result = read_buffer(fd, buffer);
	if (result < 1)
		free_string(buffer);
	return (result);
}

static void	make_line(char *buffer, char **storage, char **new_line, int idx)
{
	free_string(storage);
	*storage = ft_strdup(&buffer[idx] + sizeof(char));
	buffer[idx] = '\0';
	*new_line = ft_strjoin(*new_line, buffer);
}

static int	read_line(int fd, char **storage, char **new_line)
{
	int		idx;
	char	*buffer;
	int		result;

	idx = 0;
	result = 0;
	buffer = NULL;
	if (*storage)
		buffer = ft_strdup(*storage);
	while (1)
	{
		if (!buffer || buffer[idx] == '\0')
		{
			idx = 0;
			if ((result = read_more(&buffer, fd, new_line)) < 1)
				return (result);
		}
		if (buffer[idx] == '\n')
		{
			make_line(buffer, storage, new_line, idx);
			return (1);
		}
		idx++;
	}
}

int			get_next_line(int fd, char **line)
{
	static char	*storage[1024];
	int			result;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE == 0 || line == NULL)
		return (-1);
	result = 0;
	new_line = NULL;
	if (!storage[fd])
	{
		if ((result = read_buffer(fd, &storage[fd])) < 1)
		{
			*line = ft_strdup("");
			return (result);
		}
	}
	result = read_line(fd, &(storage[fd]), &new_line);
	if (result == 0)
		free_string(&storage[fd]);
	if (new_line == NULL)
		new_line = ft_strdup("");
	*line = new_line;
	return (result);
}
