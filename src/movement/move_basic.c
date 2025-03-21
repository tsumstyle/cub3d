/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:41 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/21 11:56:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->dir_x * player->move_speed;
	new_y = player->y + player->dir_y * player->move_speed;
	
	if (map[(int)(player->y)][(int)(new_x)] != '1')
		player->x = new_x;
	if (map[(int)(new_y)][(int)(player->x)] != '1')
		player->y = new_y;
}

void	move_backward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->x - player->dir_x * player->move_speed;
	new_y = player->y - player->dir_y * player->move_speed;
	
	if (map[(int)(player->y)][(int)(new_x)] != '1')
		player->x = new_x;
	if (map[(int)(new_y)][(int)(player->x)] != '1')
		player->y = new_y;
}

void	strafe_left(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->x - player->plane_x * player->move_speed;
	new_y = player->y - player->plane_y * player->move_speed;
	
	if (map[(int)(player->y)][(int)(new_x)] != '1')
		player->x = new_x;
	if (map[(int)(new_y)][(int)(player->x)] != '1')
		player->y = new_y;
}

void	strafe_right(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->plane_x * player->move_speed;
	new_y = player->y + player->plane_y * player->move_speed;
	
	if (map[(int)(player->y)][(int)(new_x)] != '1')
		player->x = new_x;
	if (map[(int)(new_y)][(int)(player->x)] != '1')
		player->y = new_y;
}
