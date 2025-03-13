/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_load_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:10:05 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/13 13:18:12 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	f_count_lines(t_data *data, const char *filename);

void	f_load_map(t_data *data, const char *filename)
{
	int	fd;
	int	i;
	int	lines;

	i = 0;
	fd = 0;
	lines = f_count_lines(data, filename);
	if (lines <= 0)
		close_program(data, "Error\nInvalid or empty map file\n");
	data->map.map = gc_malloc(data, sizeof(char *) * (lines + 1));  // TODO: gc_malloc?
	if (!data->map.map)
		close_program(data, "Error\nCan't allocate enough memory for the map\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		close_program(data, "Error\nFailed to open file\n");
	while (i < lines)
	{
		data->map.map[i] = gc_gnl(data, fd);
		if (!data->map.map[i])
			break ;
		i++;
	}
	data->map.map[i] = NULL;
	close(fd);
}

int	f_count_lines(t_data *data, const char *filename)
{
	int		lines;
	char	*line;
	int		fd;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = gc_gnl(data, fd);
	while (line != NULL)
	{
		// free(line); //freed by the garbage collector
		lines++;
		line = gc_gnl(data, fd);
	}
	close(fd);
	return (lines);
}