/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:57:20 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/24 10:21:55 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_data *game)
{
	if (keysym == W_KEY || keysym == UP)
		move_forward(&game->player, game->map.map);
	if (keysym == S_KEY || keysym == DOWN)
		move_backward(&game->player, game->map.map);
	if (keysym == A_KEY)
		strafe_left(&game->player, game->map.map);
	if (keysym == D_KEY)
		strafe_right(&game->player, game->map.map);
	if (keysym == LEFT)
		rotate_left(&game->player);
	if (keysym == RIGHT)
		rotate_right(&game->player);
	if (keysym == ESC || keysym == Q_KEY)
		close_program(game, "bye bye\n");
	return (0);
}

