/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:31 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/09 14:22:18 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* We cast rays from the player to the wall and each ray is gonna be a vertical
 slice on the field of view (what we see in the window), We loop over each slice */
int	render_game(t_data *data)
{
	int	slice;

	if (!data->img.ptr || !data->img.addr) //Ensure image is initialized
		return (1);
	slice = 0;
	while (slice < WIDTH)
	{
		cast_ray(data, slice);
		slice++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0); // function of the mlx library
	return (0);
}

/* Trig approach, with values in radians
	for each slice, we calculate where the slice is regarding the center of
	the field of view (window) and calculate the angle of the ray, 
	then the distance to the wall,
	then we draw the wall
*/
void	cast_ray(t_data *data, int slice)
{
	double	fov;	//field of view
	double	offset;  //relative position in the view plane (left = -1, center = 0, right = 1).
	double	ray_angle;
	double	wall_dist;
	char	side_hit;

	fov = PI / 3.0; // 60 degree angle (or PI/3 in radians): standard convention
	offset = (2.0 * slice / (double)WIDTH) - 1.0; //range [-1, 1] : gives us a relative position in the view plane (left = -1, center = 0, right = 1).
	ray_angle = data->player.angle + (offset * (fov / 2.0));
//	side_hit = 'N';  // initialize side_hit to be north, then modify if not
	wall_dist = calculate_wall_distance(data, ray_angle, &side_hit, false);
	draw_slice(data, slice, wall_dist, side_hit);
}

/* To calculate the distance to the wall, we progress step by step
	at each step, we check if we hit a wall; if so, we break the process
	we then apply a fish-eye correction because otherwise it looks weird */
double	calculate_wall_distance(t_data *data, double ray_angle, char *side_hit, bool minimap)
{
	double	wall_dist;
	double	ray_x;
	double	ray_y;
	int		grid_x;
	int		grid_y;

	wall_dist = 0.0;
	ray_x = data->player.x;
	ray_y = data->player.y;
	while (1)
	{
		ray_x += cos(ray_angle) * 0.01;  // we arbitrary define a "step" size of 0.01 for walk down the ray
		ray_y += sin(ray_angle) * 0.01;
		wall_dist += 0.01;
		grid_x = (int)ray_x;
		grid_y = (int)ray_y;
		if (grid_x < 0 || grid_x >= data->map.width \
		|| grid_y < 0 || grid_y >= data->map.height)
			return (1000000.0); // big distance, treats as very far away
		if (data->map.map[grid_y][grid_x] == '1')
			break;
	}
	if (fabs(cos(ray_angle)) > fabs(sin(ray_angle))) // this is to try to determine the orientation of the walls (to color them accordingly), but it's not fully working
	{
		if (cos(ray_angle) > 0)
			*side_hit = 'E';
		else
			*side_hit = 'W';
	}
	else
	{
		if (sin(ray_angle) > 0)
			*side_hit = 'S';
		else
			*side_hit = 'N';
	}
	if (minimap == false)
		wall_dist *= cos(ray_angle - data->player.angle); //fisheye correction
	return (wall_dist);
}

/* We have to calculate where the wall starts and  where it ends
	then draw it 
	then we draw the floor and ceiling */
void	draw_slice(t_data *data, int slice, double wall_dist, char side_hit)
{
	int	line_height;
	int	start;
	int	end;
	int	color;
	int	i;

	if (wall_dist < 0.0001)
		wall_dist = 0.0001; // avoid dividing by zero when wall distance is zero
	line_height = (int)(HEIGHT / wall_dist);
	start = -line_height / 2 + HEIGHT / 2; // where to start drawing the wall
	end = line_height / 2 + HEIGHT / 2;
	// clamp the drawing to fit the screen dimensions
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	if (side_hit == 'N')
		color = 0x404040; // placeholder wall color (replace with textures)
	else if (side_hit == 'S')
		color = 0xA0A0A0;
	else if (side_hit == 'E')
		color = 0x808080;
	else
		color = 0x606060;
	i = start;
	while (i < end)
	{
		put_pixel_to_image(data, slice, i, color);
		i++;
	}
	draw_floor_ceiling(data, slice, start, end);
}


/* DDA approach: less easy to understand but Toby said it might be more efficient
also makes the determination of wall orientation easier */
/* void	draw_each_slice(t_data *data, int slice)
{
	int	y;
	double	wall_dist;
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

	offset = 2 * slice / (double)WIDTH - 1;  // we calculate an offset (varies between -1 and 1) based on how far away the slice is from the center of the projection plane
	ray_x = data->player.dir_x + data->player.plane_x * offset;
	ray_y = data->player.dir_y + data->player.plane_y * offset;

	//To perform ray casting, we need to know in which cell of the grid the player is located, so we convert his coordinates into grid coordinates (int)
	grid_x = (int)data->player.x; 
	grid_y = (int)data->player.y;

	// we want to know which ray will hit next the grid, so we calculate delta x and y to know which one is shorter
	delta_x = fabs(1 / ray_x); // fabs(): absolute value of a floating point number
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


/* As in fractol, we draw and color each pixel of the image buffer individually 
	before loading the image to the window */
void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*pxl;

	if (!data || !data->img.addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pxl = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)pxl = color;
}
