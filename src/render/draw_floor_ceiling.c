/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:28:34 by aroux             #+#    #+#             */
/*   Updated: 2025/05/09 08:55:41 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_data *data, int slice, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
		put_pixel_to_image(data, slice, y++, 0x87CEEB);
	y = end;
	while (y < HEIGHT)
		put_pixel_to_image(data, slice, y++, 0x228B22);
}
