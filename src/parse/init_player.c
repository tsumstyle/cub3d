/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:40:20 by aroux             #+#    #+#             */
/*   Updated: 2025/05/13 14:37:08 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, char **map, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
				|| map[i][j] == 'W')
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				init_angle(data, map, i, j);
				init_dir_plane_rot_move(data);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_dir_plane_rot_move(t_data *data)
{
	data->player.dir_x = cos(data->player.angle);
	data->player.dir_y = sin(data->player.angle);
	data->player.plane_x = -data->player.dir_y;
	data->player.plane_y = data->player.dir_x;
	data->player.move_speed = 0.1;
	data->player.rot_speed = 0.05;
}

void	init_angle(t_data *data, char **map, int i, int j)
{
	if (map[i][j] == 'E')
	{
		data->player.angle = 0;
		data->player.orientation = 'E';
	}
	if (map[i][j] == 'N')
	{
		data->player.angle = PI / 2;
		data->player.orientation = 'N';
	}
	if (map[i][j] == 'W')
	{
		data->player.angle = PI;
		data->player.orientation = 'W';
	}
	if (map[i][j] == 'S')
	{
		data->player.angle = 3 * PI / 2;
		data->player.orientation = 'S';
	}
}
