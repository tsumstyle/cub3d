/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:51:21 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/14 14:27:16 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_game(t_data *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_input, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, handle_close, game);
	mlx_loop(game->mlx);
}

void	launch_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (data->win == NULL)
	{
		free_img_win_mlx(data, "New window creation failed");
		exit (1);
	}
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.ptr)
	{
		free_img_win_mlx(data, "Image creation failed");
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bpp, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		free_img_win_mlx(data, "Failed to get image address");
		exit(1);
	}
}

int	game_loop(t_data *game)
{
	update_sprites(game);
	render_game(game);
	draw_minimap(game);
	return (0);
}
