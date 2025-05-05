/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:31 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/05 16:12:15 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_game(t_data *data)
{
	int	slice;

	if (!data->img.ptr || !data->img.addr) //Ensure image is initialized
		return (1);
	slice = 0;
	while (slice < WIDTH)
	{
		draw_each_slice(data, slice);
		slice++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0); // function of the mlx library
	return (0);
}

void	draw_each_slice(t_data *data, int slice)
{
	int	y;
	int	wall_dist;
	int	start;
	int	end;
	int	line_height;

	wall_dist = 1.0 + slice * 0.01; 		// replace it with a calculate_wall_distance() function that uses DDA
	// wall_dist = calculate_wall_dist();
	line_height = (int)(HEIGHT / wall_dist);// calculates how tall the wall should appear on screen
	start = -line_height / 2 + HEIGHT / 2;	// centers wall slice vertically
	if (start < 0) 							// if the wall is bigger than the height, we clamp it to 0 to stay on screen
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = start;
	while (y < end)
	{
		put_pixel(data, slice, y, 0x00FF00); // placeholder wall color (replace with textures)
		y++;
	}
}

/* Casting a ray from the player's position at a certain angle, determined by
	how far off-center that slice is */
int	calculate_wall_dist(t_data *data, int slice, int dist)
{
	double	offset;
	double	ray_x;
	double	ray_y;

	offset = 2 * slice / (double)WIDTH - 1;  // we calculate an offset (varies between -1 and 1) based on how far away the slice is from the center of the projection plane
	ray_x = data->player.dir_x + data->player.plane_x * offset;
	ray_y = data->player.dir_y + data->player.plane_y * offset;
	// DDA
	// wall hit side (for shading / texturing)
}

/* As in fractol, we draw and color each pixel of the image buffer individually 
	before loading the image to the window */
void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pxl;

	pxl = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)pxl = color;
}
