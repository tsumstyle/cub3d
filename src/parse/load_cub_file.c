/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:10:05 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/19 15:48:44 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(t_data *data, const char *filename);

void	load_cub_file(t_data *data, const char *filename)
{
	int	fd;
	int	i;
	int	lines;

	i = 0;
	fd = 0;
	lines = count_lines(data, filename);
	if (lines <= 0)
		close_program(data, "Error\nInvalid or empty .cub file\n");
	data->map.file = gc_malloc(data, sizeof(char *) * (lines + 1));
	if (!data->map.file)
		close_program(data, "Error\nCan't allocate memory for the .cub file\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		close_program(data, "Error\nFailed to open file\n");
	while (i < lines)
	{
		data->map.file[i] = gc_gnl(data, fd);
		if (!data->map.file[i])
			break ;
		i++;
	}
	data->map.file[i] = NULL;
	close(fd);
}

void	load_map(t_data *data, int n)
{
	int	i;
	int	j;

	i = 0;
	while (get_line_type(data->map.file[i]) != L_MAP)
		i++;
	if (n <= i)
	{
		data->map.n_map_lines = 0;
		return ;
	}
	data->map.map = gc_malloc(data, sizeof(char *) * (n - i + 1));
	if (!data->map.map)
		close_program(data, "Error\nCan't allocate memory for the map\n");
	j = 0;
	while (i < n && data->map.file[i] && \
		get_line_type(data->map.file[i]) == L_MAP)
	{
		data->map.map[j] = data->map.file[i];
		i++;
		j++;
	}
	data->map.map[j] = NULL;
	data->map.n_map_lines = j;
}

int	count_lines(t_data *data, const char *filename)
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
		lines++;
		line = gc_gnl(data, fd);
	}
	close(fd);
	return (lines);
}
