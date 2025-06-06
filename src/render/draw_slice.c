/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:13:54 by aroux             #+#    #+#             */
/*   Updated: 2025/05/15 16:12:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* We have to calculate where the wall starts and  where it ends
	then draw it 
	then we draw the floor and ceiling */
void	draw_slice(t_data *data, int slice, double wall_dist)
{
	int	start;
	int	end;
	int	i;

	if (wall_dist < 0.1)
		wall_dist = 0.1;
	data->wall_height = (int)(HEIGHT / wall_dist);
	start = -data->wall_height / 2 + HEIGHT / 2;
	end = data->wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	i = start;
	while (i < end)
	{
		draw_wall_pixel(data, slice, i, start);
		i++;
	}
	draw_floor_ceiling(data, slice, start, end);
}

void	draw_wall_pixel(t_data *data, int x, int y, int start)
{
	t_img			tex;
	unsigned char	*color;
	int				text_x;
	int				text_y;
	double			relative_hit_pos;

	tex = get_texture(data);
	if (data->wall_orient == 'N' || data->wall_orient == 'S')
		relative_hit_pos = data->wall_hit_x - floor(data->wall_hit_x);
	else
		relative_hit_pos = data->wall_hit_y - floor(data->wall_hit_y);
	text_x = (int)(relative_hit_pos * TEXT_WIDTH);
	if (text_x < 0)
		text_x = 0;
	if (text_x >= TEXT_WIDTH)
		text_x = TEXT_WIDTH - 1;
	text_y = (int)((y - start) / (double)data->wall_height * TEXT_HEIGHT);
	if (text_y < 0)
		text_y = 0;
	if (text_y >= TEXT_HEIGHT)
		text_y = TEXT_HEIGHT - 1;
	color = (unsigned char *)(tex.addr + \
	(text_y * tex.line_len + text_x * (tex.bpp / 8)));
	blend_fog_rgb(data, color);
	put_pixel_to_image_rgb(data, x, y);
}

t_img	get_texture(t_data *data)
{
	t_img	texture;

	if (data->wall_orient == 'N')
		texture = data->text_n;
	else if (data->wall_orient == 'S')
		texture = data->text_s; 
	else if (data->wall_orient == 'E')
		texture = data->text_e; 
	else
		texture = data->text_w;
	return (texture);
}

void	put_pixel_to_image_rgb(t_data *data, int x, int y)
{
	unsigned char	*pxl;

	if (!data || !data->img.addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pxl = (unsigned char *)data->img.addr + \
			(y * data->img.line_len + x * (data->img.bpp / 8));
	pxl[0] = data->cal_out.r;
	pxl[1] = data->cal_out.g;
	pxl[2] = data->cal_out.b;
}
