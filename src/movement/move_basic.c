/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:41 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/21 11:09:34 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, char **map)
{
	if (map[(int)(player->y)]\
	[(int)(player->x + player->dir_x * player->move_speed)] != '1')
		player->x += player->dir_x * player->move_speed;
	if (map[(int)(player->y + player->dir_y * player->move_speed)]\
	[(int)(player->x)] != '1')
		player->y += player->dir_y * player->move_speed;
}

void	move_backwards(t_player *player, char **map)
{
	if (map[(int)(player->y)]\
	[(int)(player->x - player->dir_x * player->move_speed)] != '1')
		player->x -= player->dir_x * player->move_speed;
	if (map[(int)(player->y - player->dir_y * player->move_speed)]\
	[(int)(player->x)] != '1')
		player->y -= player->dir_y * player->move_speed;
}

void	strafe_left(t_player *player, char **map)
{
	if (map[(int)(player->y)]\
	[(int)(player->x - player->plane_x * player->move_speed)] != '1')
		player->x -= player->plane_x * player->move_speed;
	if (map[(int)(player->y - player->plane_y * player->move_speed)]\
	[(int)(player->x)] != '1')
		player->y -= player->plane_y * player->move_speed;
}

void	strafe_left(t_player *player, char **map)
{
	if (map[(int)(player->y)]\
	[(int)(player->x + player->plane_x * player->move_speed)] != '1')
		player->x += player->plane_x * player->move_speed;
	if (map[(int)(player->y + player->plane_y * player->move_speed)]\
	[(int)(player->x)] != '1')
		player->y += player->plane_y * player->move_speed;
}
