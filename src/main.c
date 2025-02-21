/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/02/21 13:03:35 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(void)
{
	t_data	data;

	data_init(&data);
	hook_events(&data);
	mlx_loop(data.mlx);

	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = NULL;
	data->img = NULL;
	data->win = NULL;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		perror("Malloc failed");
		exit (1);
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		perror("Malloc failed");
		exit (1);
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
		free_data(data);
		exit (0); 
	}
	// define other key events
	return (0);
}

int	close_program(t_data *data)
{
	free_data(data);  //free whatever we need to before exiting. Garbage collector?
	exit(0);
	return (0);
}

void	free_data(t_data *data)
{
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}
