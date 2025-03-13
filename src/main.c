/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/03/13 13:21:04 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* The beginning of Cub3D is a mix of concepts from Fract-ol and So Long:

    From Fract-ol:
    ✅ Using MiniLibX to create a window and draw pixels
    ✅ Modifying an image buffer before displaying it

    From So Long:
    ✅ Handling player movement with keyboard inputs
    ✅ Parsing a map file and rendering a grid-based world

Once these basics are done, Cub3D goes further with:
✅ Ray-casting to create a 3D perspective
✅ Textures & shading for walls
✅ Advanced movement (rotation, strafing, collisions, etc.) 

UPDATE 1203 B:
	- Changed get_next_line
	- Map is loading
	- No memory leaks

NEXT STEPS:
	- Extract textures, colors, and the map from the dummy map */

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (f_check_command_line_arguments(argc, argv) != 0)
		return (1);
	data_init(&data);
	f_parser(&data, argv[1]);
	//hook_events(&data);
	//mlx_loop_hook(data.mlx, render_image, &data);
	//mlx_loop(data.mlx);
	close_program(&data, "bye bye");
	return (0);
}

void	data_init(t_data *data)
{
	data->gc_list = NULL;
	data->mlx = NULL;
	data->img = NULL;
	data->win = NULL;
	data->line_len = WIDTH;
	data->map.map = NULL;
	// intializind the connection
	/*data->mlx = mlx_init();
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
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		perror("Image creation failed");
		exit (1);
	}
	// stores the address of the image:
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);*/
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

int	close_program(t_data *data, char *msg)
{
	printf("%s", msg);
	free_data(data); //free whatever we need to before exiting. Garbage collector?
	gc_free_all(data);
	exit(0);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
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

/* As in fractol, we draw and color each pixel of the image buffer individually 
	before loading the image to the window 
void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pxl;

	pxl = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)pxl = color;
}*/

/* We iterate through each line of the image and draw pixel by pixel, then line 
	by line 
int	render_image(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < 300)
				put_pixel(data, x, y, 0x00FF00); // color in green the top half
			else
				put_pixel(data, x, y, 0x0000FF);	// color in blue the bottom half
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0); // function of the mlx library
	return (0);
}*/