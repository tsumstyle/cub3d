/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:54:59 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/05 14:01:18 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

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