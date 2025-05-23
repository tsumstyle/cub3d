/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:27:13 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/16 10:54:19 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	clamp(double x, double lo, double hi)
{
	if (x < lo)
		return (lo);
	else if (x > hi)
		return (hi);
	else
		return (x);
}

void	blend_fog_rgb(t_data *data, unsigned char *p)
{
	double		f;

	data->orig.r = p[0];
	data->orig.g = p[1];
	data->orig.b = p[2];
	data->fog.r = FOG_COLOR;
	data->fog.g = FOG_COLOR;
	data->fog.b = FOG_COLOR;
	f = clamp(1.0 - (data->wall_dist / FOG_DISTANCE), 0.0, 1.0);
	data->cal_out.r = (unsigned char)(f * data->orig.r + \
		(1.0 - f) * data->fog.r);
	data->cal_out.g = (unsigned char)(f * data->orig.g + \
		(1.0 - f) * data->fog.g);
	data->cal_out.b = (unsigned char)(f * data->orig.b + \
		(1.0 - f) * data->fog.b);
}

void	blend_fog_rgb_ceiling(t_data *data, unsigned char *p, double y, \
								double start)
{
	double		f;
	double		rel;

	data->orig.r = p[0];
	data->orig.g = p[1];
	data->orig.b = p[2];
	data->fog.r = FOG_COLOR;
	data->fog.g = FOG_COLOR;
	data->fog.b = FOG_COLOR;
	if (start > 0)
		rel = y / ((HEIGHT - 50) / 2);
	else
		rel = 1.0;
	f = clamp(1 - rel, 0.0, 1.0);
	data->cal_out.r = (unsigned char)(f * data->orig.r + \
		(1.0 - f) * data->fog.r);
	data->cal_out.g = (unsigned char)(f * data->orig.g + \
		(1.0 - f) * data->fog.g);
	data->cal_out.b = (unsigned char)(f * data->orig.b + \
		(1.0 - f) * data->fog.b);
}

void	blend_fog_rgb_floor(t_data *data, unsigned char *p, double y, \
							double end)
{
	double		f;
	double		rel;

	data->orig.r = p[0];
	data->orig.g = p[1];
	data->orig.b = p[2];
	data->fog.r = FOG_COLOR;
	data->fog.g = FOG_COLOR;
	data->fog.b = FOG_COLOR;
	if (end < HEIGHT)
		rel = (HEIGHT - y) / ((HEIGHT + 10) / 2.0);
	else
		rel = 1.0;
	f = clamp(1.0 - rel, 0.0, 1.0);
	data->cal_out.r = (unsigned char)(f * data->orig.r + \
		(1.0 - f) * data->fog.r);
	data->cal_out.g = (unsigned char)(f * data->orig.g + \
		(1.0 - f) * data->fog.g);
	data->cal_out.b = (unsigned char)(f * data->orig.b + \
		(1.0 - f) * data->fog.b);
}

void	draw_floor_ceiling(t_data *data, int slice, int start, int end)
{
	int		y;

	y = 0;
	while (y < start)
	{
		blend_fog_rgb_ceiling(data, data->ceiling_color, y, start);
		put_pixel_to_image_rgb(data, slice, y);
		y++;
	}
	y = end;
	while (y < HEIGHT)
	{
		blend_fog_rgb_floor(data, data->floor_color, y, end);
		put_pixel_to_image_rgb(data, slice, y);
		y++;
	}
}
