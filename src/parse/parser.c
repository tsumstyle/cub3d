/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:23:25 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/24 15:33:39 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* 2403 A: Tested all the maps and they now all seem to work! */

void	parser(t_data *data, const char *filename)
{
	int	n;

	n = count_lines(data, filename);
	load_cub_file(data, filename);
	if (!data->map.file || !data->map.file[0])
		clean_exit(data, "Error\nEmpty .cub file\n");
	if (check_each_line(data, n) == 1)
		clean_exit(data, "Error\nInvalid .cub file\n");
	if (check_each_line(data, n) == 2)
		clean_exit(data, "Error\nInvalid file: too few or too many values\n");
	if (check_map_last(data->map.file, n) == 2)
		clean_exit(data, "Error\nInvalid file: map should be at the end\n");
	if (check_map_last(data->map.file, n) == 3)
		clean_exit(data, "Error\nInvalid file: char after end of map\n");
	if (check_map_last(data->map.file, n) == 4)
		clean_exit(data, "Error\nInvalid file: no map\n");
	load_map(data, n);
	if (check_map(data->map.map, data->map.n_map_lines) == 1)
		clean_exit(data, "Error\nInvalid map: Should have enclosed walls\n");
	if (check_map(data->map.map, data->map.n_map_lines) == 2)
		clean_exit(data, "Error\nInvalid map: Should have one unique \
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
