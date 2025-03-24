/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/03/24 15:39:31 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* UPDATE 2403 A:
	- checked all maps: good ones pass, bad ones don't, no leak and no segfault
	- separated data_init() from lauching the window, mlx, etc (after parsing)
	so if a map is invalid, it does not open a window just to close it, 
	it quits before with clean_exit()

NEXT STEPS:
	- Extract textures, colors, and the map from the dummy map */

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_command_line_arguments(argc, argv) != 0)
		return (1);
	data_init(&data);
	parser(&data, argv[1]);
	launch_window(&data);
	//hook_events(&data);
	//mlx_loop_hook(data.mlx, render_image, &data);
	//mlx_loop(data.mlx);
	run_game(&data);
	//close_program(&data, "bye bye");
	return (0);
}

void	data_init(t_data *data)
{
	data->gc_list = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->line_len = WIDTH;
	data->map.file = NULL;
	data->map.map = NULL;
}

void	launch_window(t_data *data)
{
	// intializind the connection
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		perror("Malloc failed");
		exit (1);
	}
	// opening new window:
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		perror("Malloc failed");
		exit (1);
	}
	// initialize image buffer: creating image buffer (init data->img) and getting its memory address (data->addr)
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.ptr)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		perror("Image creation failed");
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
}

/* function to define the different hook events: 
		key press, 
		mouse move, 
		mouse clic,
		etc
	for now: i just defined ESC and clic on the window cross 
	to exit the window in a clean way */
void	hook_events(t_data *data)
{
	mlx_key_hook(data->win, key_press, data);
	mlx_hook(data->win, 17, 1L << 17, close_program, data);
	return ;
}

/* define the key presses. For now just ESC to exit */
int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		free_img_win_mlx(data);
		exit (0); 
	}
	// define other key events
	return (0);
}
