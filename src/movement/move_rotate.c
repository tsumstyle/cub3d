/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:54:59 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/13 14:29:21 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	player->angle -= player->rot_speed;
	if (player->angle < 0)
		player->angle += 2 * PI;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) - \
	player->dir_y * sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed) + \
	player->dir_y * cos(-player->rot_speed);
	player->plane_x = player->plane_x * cos(-player->rot_speed) - \
	player->plane_y * sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed) + \
	player->plane_y * cos(-player->rot_speed);
}

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	player->angle += player->rot_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(player->rot_speed) - \
	player->dir_y * sin(player->rot_speed);
	player->dir_y = old_dir_x * sin(player->rot_speed) + \
	player->dir_y * cos(player->rot_speed);
	player->plane_x = player->plane_x * cos(player->rot_speed) - \
	player->plane_y * sin(player->rot_speed);
	player->plane_y = old_plane_x * sin(player->rot_speed) + \
	player->plane_y * cos(player->rot_speed);
}
