/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:36:24 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/14 14:39:08 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '\n')
			{
				x++;
				continue ;
			}
			else if (game->map.map[y][x] != '1')
				draw_square(game, x, y, MINI_FLOOR_COLOR);
			else
				draw_square(game, x, y, MINI_WALL_COLOR);
			x++;
		}
		y++;
	}
	draw_minimap_fov(game);
	draw_minimap_player_and_pov(game);
}

void	draw_square(t_data *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < MINI_TILE_SIZE)
	{
		j = 0;
		while (j < MINI_TILE_SIZE)
		{
			px = MAP_OFFSET_X + x * MINI_TILE_SIZE + j;
			py = MAP_OFFSET_Y + y * MINI_TILE_SIZE + i;
			put_pixel_to_image(game, px, py, color);
			j++;
		}
		i++;
	}
}

void	draw_square_pixel(t_data *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_PLAYER_SIZE)
	{
		j = 0;
		while (j < MINI_PLAYER_SIZE)
		{
			put_pixel_to_image(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player_and_pov(t_data *game)
{
	int	p_x;
	int	p_y;
	int	pov_x;
	int	pov_y;

	p_x = MAP_OFFSET_X + game->player.x * MINI_TILE_SIZE;
	p_y = MAP_OFFSET_Y + game->player.y * MINI_TILE_SIZE;
	pov_x = p_x + game->player.dir_x * MINI_TILE_SIZE * 2;
	pov_y = p_y + game->player.dir_y * MINI_TILE_SIZE * 2;
	draw_square_pixel(game, p_x - MINI_PLAYER_SIZE / 2, \
	p_y - MINI_PLAYER_SIZE / 2, 0xFF0000);
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*pxl;
	
	if (!data || !data->img.addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pxl = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)pxl = color;
}
