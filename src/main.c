/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/05/09 08:52:00 by bbierman         ###   ########.fr       */
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
	//open_window(&data);
	launch_window(&data);   // 0705A: we have two functions that achieve the same thing and I'm not sure why: launch_window and open_window; I changed launch_window so it's cleaner and only 25 lines
	mlx_loop_hook(data.mlx, game_loop, &data);
	//hook_events(&data);
	//mlx_loop(data.mlx);
	run_game(&data);
	//close_program(&data, "bye bye");
	return (0);
}

void	data_init(t_data *data)
{
	ft_bzero(data, sizeof(*data));
	data->line_len = WIDTH;
}

void	launch_window(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		perror("Malloc failed");
		exit (1);
	}
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
		free_img_win_mlx(data, NULL);
		exit (0); 
	}
	// define other key events
	return (0);
}
