/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:23:25 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/13 16:33:46 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	f_parser(t_data *data, const char *filename)
{
	int	n_lines;

	n_lines = f_count_lines(data, filename);
	f_load_map(data, filename);
	f_print_map(data->map.map);
	// check map is valid
	if (!data->map.map || !data->map.map[0])
		close_program(data, "Error\nEmpty map\n");
	if (check_map(data->map.map, n_lines) == 1)
		close_program(data, "Error\nInvalid map:\nShould have enclosed walls");
	if (check_map(data->map.map, n_lines) == 2)
		close_program(data, "Error\nInvalid map:\nShould have one unique \
			player");
	// 
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
