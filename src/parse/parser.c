/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:23:25 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/19 15:58:08 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: 1903A: test invalid .cub files ("bad maps") and see 
// if error handling works properly for all 

void	parser(t_data *data, const char *filename)
{
	int	n;

	n = count_lines(data, filename);
	// map.file -> loaded already
	// map.map -> TODO: load the map itself
	load_cub_file(data, filename);
	load_map(data, n);
	print_cub_file(data->map.file);
	if (!data->map.file || !data->map.file[0])
		close_program(data, "Error\nEmpty .cub file\n");
	if (check_each_line(data, n) == 1)
		close_program(data, "Error\nInvalid .cub file\n");
	if (check_map(data->map.map, data->map.n_map_lines) == 1)
		close_program(data, "Error\nInvalid map: Should have enclosed walls\n");
	if (check_map(data->map.map, data->map.n_map_lines) == 2)
		close_program(data, "Error\nInvalid map: Should have one unique \
			player\n");
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
