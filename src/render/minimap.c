/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:36:24 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/21 15:17:33 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map.map[x]) //Dont know if this is going to work 
	{
		y = 0;
		while (game->map.map[x][y])
		{
			if (game->map.map[x][y] != '1')
				draw_square(game, x, y, MINI_FLOOR_COLOR);
			else
				draw_square(game, x, y, MINI_WALL_COLOR);
			y++;
		}
		x++;
	}
	draw_minimap_player_and_pov(game);
}

void	draw_square(t_data *game, int x, int y, int color)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < MINI_TILE_SIZE)
	{
		j = 0;
		while (j < MINI_TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, x + j, y + i, color);
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

	p_x = game->player.x * MINI_PLAYER_SIZE;
	p_y = game->player.y * MINI_PLAYER_SIZE;
	pov_x = p_x + game->player.dir_x * MINI_TILE_SIZE * 2;
	pov_y = p_y + game->player.dir_y * MINI_TILE_SIZE * 2;
	draw_square(game, p_x - MINI_PLAYER_SIZE / 2, p_y - MINI_PLAYER_SIZE / 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, pov_x, pov_y, 0x00FF00);
}