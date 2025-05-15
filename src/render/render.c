/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:31 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/15 16:10:49 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* We cast rays from the player to the wall and each ray is gonna be a vertical
slice on the field of view (what we see in the window) */
int	render_game(t_data *data)
{
	int	slice;

	if (!data->img.ptr || !data->img.addr)
		return (1);
	slice = 0;
	while (slice < WIDTH)
	{
		cast_ray(data, slice);
		slice++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}

/* Trig approach, with values in radians
	for each slice, we calculate where the slice is regarding the center of
	the field of view (window) and calculate the angle of the ray, 
	then the distance to the wall,
	then we draw the wall */
void	cast_ray(t_data *data, int slice)
{
	double	fov;
	double	ray_angle;
	double	wall_dist;
	double	offset;

	fov = PI / 3.0;
	offset = (2.0 * slice / (double)WIDTH) - 1.0;
	ray_angle = data->player.angle + (offset * (fov / 2.0));
	wall_dist = calculate_wall_distance(data, ray_angle, false);
	data->wall_dist = wall_dist;
	draw_slice(data, slice, wall_dist);
}

/* DDA approach: less easy to understand but Toby said it might be more 
efficient, also makes the determination of wall orientation easier
 void	draw_each_slice(t_data *data, int slice)
{
	int	y;
	double	wall_dist;
	int	start;
	int	end;
	int	line_height;

	wall_dist = 1.0 + slice * 0.01; 		
	// wall_dist = calculate_wall_dist();
	line_height = (int)(HEIGHT / wall_dist);
	start = -line_height / 2 + HEIGHT / 2;	
	if (start < 0) 					
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = start;
	while (y < end)
	{
		put_pixel(data, slice, y, 0x00FF00);
		y++;
	}
}

// DDA: 
//	Casting a ray from the player's position at a certain angle, determined by
//	how far off-center that slice is
double	calculate_wall_dist(t_data *data, int slice)
{
	double	offset;
	double	ray_x;
	double	ray_y;

	int		grid_x;
	int		grid_y;

	double	delta_x;
	double	delta_y;

	int		step_x;
	int		step_y;
	int		first_step_x;
	int		first_step_y;

	int		hit;
	int		yside;

	double	wall_dist;

	offset = 2 * slice / (double)WIDTH - 1;  
	ray_x = data->player.dir_x + data->player.plane_x * offset;
	ray_y = data->player.dir_y + data->player.plane_y * offset;

	//To perform ray casting, we need to know in which cell of the grid 
the player is located, so we convert his coordinates into grid coordinates (int)
	grid_x = (int)data->player.x; 
	grid_y = (int)data->player.y;

	// we want to know which ray will hit next the grid, so we calculate delta x 
	and y to know which one is shorter
	delta_x = fabs(1 / ray_x);
	delta_y = fabs(1 / ray_y);

	//determine step direction and initial side distances
	if (ray_x < 0)
	{
		step_x = -1;
		first_step_x = (data->player.x - grid_x) * delta_x;
	}
	else
	{
		step_x = 1;
		first_step_x = (grid_x + 1.0 - data->player.x) * delta_x;
	}
	if (ray_y < 0)
	{
		step_y = -1;
		first_step_y = (data->player.y - grid_y) * delta_y;
	}
	else
	{
		step_y = 1;
		first_step_y = (grid_y + 1.0 - data->player.y) * delta_y;
	}

	//check wall hit
	hit = 0;
	while (hit == 0)
	{
		if (first_step_x < first_step_y)
		{
			first_step_x += delta_x;
			grid_x = grid_x + step_x;
			yside = 0; // hit on x-side;
		}
		else
		{
			first_step_y += delta_y;
			grid_y += step_y;
			yside = 1; // hit on y-side
		}
		if (data->map[grid_y][grid_x] == '1')
			hit = 1;
	}
	if (yside == 0)
		wall_dist = (grid_x - data->player.x + (1 - step_x) / 2) / ray_x;
	else
		wall_dist = (grid_y - data->player.y + (1 - step_y) / 2) / ray_y;
	return (wall_dist);
	// wall hit side (for shading / texturing)
}
*/
