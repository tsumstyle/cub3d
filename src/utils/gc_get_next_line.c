/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:37:49 by aroux             #+#    #+#             */
/*   Updated: 2025/03/13 13:18:59 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_join_buffer(char *s1, char *s2);
static char	*ft_read_file(int fd, char *buffer);
static char	*ft_get_myline(t_data *data, char *buffer);
static char	*ft_get_tail(char *buffer);

char	*gc_gnl(t_data * data, int fd)
{
	char		*buffer;
	char		*line;
	static char	*tail;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	if (tail)
		buffer = ft_join_buffer(buffer, tail);
	free(tail);
	tail = NULL;
	buffer = ft_read_file(fd, buffer);
	line = ft_get_myline(data, buffer);
	tail = ft_get_tail(buffer);
	free(buffer);
	buffer = NULL;
	return (line);
}

static char	*ft_join_buffer(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	free(s1);
	s1 = NULL;
	return (result);
}

static char	*ft_read_file(int fd, char *buffer)
{
	int		bytes_read;
	char	*temp_buffer;

	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			free(buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		buffer = ft_join_buffer(buffer, temp_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	temp_buffer = NULL;
	return (buffer);
}

static char	*ft_get_myline(t_data *data, char *buffer)
{
	int		i;
	char	*line;

	if (!buffer || *buffer == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = gc_malloc(data, i + 2 * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i++] = '\0';
	return (line);
}

static char	*ft_get_tail(char *buffer)
{
	int			i;
	static char	*tail;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	tail = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	if (!tail || *tail == '\0')
	{
		free(tail);
		tail = NULL;
	}
	return (tail);
}
