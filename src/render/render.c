/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:31 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/21 17:09:03 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* We iterate through each line of the image and draw pixel by pixel, then line 
	by line */
int	render_game(t_data *data)
{
	int	x;
	int	y;

	if (!data->img.ptr || !data->img.addr) // ✅ Ensure image is initialized
		return (1);

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
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0); // function of the mlx library
	return (0);
}

/* As in fractol, we draw and color each pixel of the image buffer individually 
	before loading the image to the window */
void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pxl;

	pxl = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)pxl = color;
}