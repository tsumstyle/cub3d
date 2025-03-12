/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_load_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:10:05 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/12 20:36:19 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	f_count_lines(const char *filename);

void	f_load_map(t_data *data, const char *filename)
{
	int	fd;
	int	i;
	int	lines;

	i = 0;
	fd = 0;
	lines = f_count_lines(filename);
	if (lines <= 0)
		close_program(data, "Error\nInvalid or empty map file\n");
	data->map.map = malloc(sizeof(char *) * (lines + 1));
	if (!data->map.map)
		close_program(data, "Error\nCan't allocate enough memory for the map\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		close_program(data, "Error\nFailed to open file\n");
	while (i < lines)
	{
		data->map.map[i] = get_next_line(fd);
		if (!data->map.map[i])
			break ;
		i++;
	}
	data->map.map[i] = NULL;
	close(fd);
}

int	f_count_lines(const char *filename)
{
	int		lines;
	char	*line;
	int		fd;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		lines++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}