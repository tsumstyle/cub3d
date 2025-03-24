/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:23:25 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/24 14:33:21 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* 2403 A: Tested all the maps and they now all seem to work! */

void	parser(t_data *data, const char *filename)
{
	int	n;

	n = count_lines(data, filename);
	load_cub_file(data, filename);
	//print_cub_file(data->map.file);
	if (!data->map.file || !data->map.file[0])
		close_program(data, "Error\nEmpty .cub file\n");
	if (check_each_line(data, n) == 1)
		close_program(data, "Error\nInvalid .cub file\n");
	if (check_each_line(data, n) == 2)
		close_program(data, "Error\nInvalid file: too few or too many values\n");
	if (check_map_last(data, n) == 2)
		close_program(data, "Error\nInvalid file: map should be at the end\n");
	if (check_map_last(data, n) == 3)
		close_program(data, "Error\nInvalid file: char after end of map\n");
	load_map(data, n);
	if (check_map(data->map.map, data->map.n_map_lines) == 1)
		close_program(data, "Error\nInvalid map: Should have enclosed walls\n");
	if (check_map(data->map.map, data->map.n_map_lines) == 2)
		close_program(data, "Error\nInvalid map: Should have one unique \
			player\n");
	printf("\n");
	print_cub_file(data->map.map);
	print_parsing_result(data);
}

int	get_max_line_len(char **map, int n)
{
	int	i;
	int	max_len;
	int	curr_len;

	max_len = 0;
	i = 8;
	while (i < n)
	{
		curr_len = 0;
		while (map[i] && map[i][curr_len])
			curr_len++;
		if (curr_len > max_len)
			max_len = curr_len;
		i++;
	}
	return (max_len);
}
