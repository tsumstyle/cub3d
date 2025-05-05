/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:51:21 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/05 16:55:42 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_game(t_data *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_input, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, handle_close, game);
	mlx_loop(game->mlx);
}
/*
void	ft_open_window(t_data *game)
{
	int	win_x;
	int	win_y;

	win_x = game->map.width * MINI_TILE_SIZE;
	win_y = game->map.height * MINI_TILE_SIZE;
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	game_loop(game);
}*/

void	ft_open_window(t_data *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		perror("Window creation failed");
		exit(1);
	}

	// ✅ Initialize image buffer before rendering
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		perror("Image creation failed");
		exit(1);
	}

	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.addr)
	{
		mlx_destroy_image(game->mlx, game->img.ptr);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		perror("Failed to get image address");
		exit(1);
	}

	// ✅ Use `mlx_loop_hook()` to update the game loop continuously
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	game_loop(t_data *game)
{
	render_game(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}