/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:55:13 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/14 12:06:29 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_fov(t_data *game)
{
	double	start_angle;
	double	end_angle;
	double	angle_step;
	double	angle;

	start_angle = -MINI_FOV / 2;
	end_angle = MINI_FOV / 2;
	angle_step = MINI_RAY_STEP;
	angle = start_angle;
	while (angle <= end_angle)
	{
		draw_minimap_ray(game, angle);
		angle += angle_step;
	}
}

void	draw_minimap_ray(t_data *game, double rel_angle)
{
	double	dir_angle;
	double	len;
	int		px;
	int		py;
	int		i;

	i = 0;
	dir_angle = atan2(game->player.dir_y, game->player.dir_x) \
	+ rel_angle * (PI / 180.0);
	len = calculate_wall_distance(game, dir_angle, true);
	if (len > MINI_RAY_LENGTH)
		len = MINI_RAY_LENGTH;
	while (i < len * MINI_TILE_SIZE)
	{
		px = MAP_OFFSET_X + game->player.x * MINI_TILE_SIZE \
						+ cos(dir_angle) * i;
		py = MAP_OFFSET_Y + game->player.y * MINI_TILE_SIZE \
						+ sin(dir_angle) * i;
		put_pixel_to_image(game, px, py, 0x00FF00);
		i++;
	}
}
