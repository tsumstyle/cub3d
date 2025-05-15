/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:54:10 by aroux             #+#    #+#             */
/*   Updated: 2025/05/15 16:09:10 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* To calculate the distance to the wall, we progress step by step
	at each step, we check if we hit a wall; if so, we break the process
	then store the coordinates of where we hit the wall (to reuse when drawing),
	then apply a fish-eye correction because otherwise it looks weird */
double	calculate_wall_distance(t_data *data, double ray_angle, bool minimap)
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
		ray_x += cos(ray_angle) * 0.01;
		ray_y += sin(ray_angle) * 0.01;
		wall_dist += 0.01;
		grid_x = (int)ray_x;
		grid_y = (int)ray_y;
		if (grid_x < 0 || grid_x >= data->map.width \
		|| grid_y < 0 || grid_y >= data->map.height)
			return (1000000.0);
		if (data->map.map[grid_y][grid_x] == '1')
			break ;
	}
	store_hit_coordinates(data, ray_x, ray_y, ray_angle);
	fisheye_correction(data, &wall_dist, ray_angle, minimap);
	return (wall_dist);
}

void	store_hit_coordinates(t_data *data, double ray_x, double ray_y, \
	double ray_angle)
{
	data->wall_hit_x = ray_x;
	data->wall_hit_y = ray_y;
	find_wall_orient(data, ray_x, ray_y, ray_angle);
}

void	find_wall_orient(t_data *data, double ray_x, double ray_y, \
	double ray_angle)
{
	int		stepback_x;
	int		stepback_y;
	int		grid_x;
	int		grid_y;

	grid_x = (int)ray_x;
	grid_y = (int)ray_y;
	stepback_x = (int)(ray_x - cos(ray_angle) * 0.01);
	stepback_y = (int)(ray_y - sin(ray_angle) * 0.01);
	if (stepback_x <= grid_x && stepback_y == grid_y)
		data->wall_orient = 'E';
	else if (stepback_x >= grid_x && stepback_y == grid_y)
		data->wall_orient = 'W';
	else if (stepback_x == grid_x && stepback_y <= grid_y)
		data->wall_orient = 'N';
	else if (stepback_x == grid_x && stepback_y >= grid_y)
		data->wall_orient = 'S';
}

void	fisheye_correction(t_data *data, double *wall_dist, double ray_angle, \
	bool minimap)
{
	if (minimap == false)
		*wall_dist *= cos(ray_angle - data->player.angle);
}
