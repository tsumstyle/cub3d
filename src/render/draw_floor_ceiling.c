/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:28:34 by aroux             #+#    #+#             */
/*   Updated: 2025/05/07 11:33:18 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_data *data, int slice, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
		put_pixel(data, slice, y++, 0x87CEEB);
	y = end;
	while (y < HEIGHT)
		put_pixel(data, slice, y++, 0x228B22);
}
