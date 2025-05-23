/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:57:50 by aroux             #+#    #+#             */
/*   Updated: 2025/05/14 15:10:38 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Calculate distance of each sprite to player
	sort the sprite array from farthest to nearest
	update dyna,mic states */
void	update_sprites(t_data *data)
{
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < data->sprite_count)
	{
		dx = data->sprites[i].x - data->player.x;
		dy = data->sprites[i].y - data->player.y;
		data->sprites[i].distance = dx * dx + dy * dy;
		if (data->sprites[i].texture_id == MUMMY_CALM_TEXT \
			&& data->sprites[i].distance < 4.0)
			data->sprites[i].texture_id = MUMMY_ANGRY_TEXT;
		else if (data->sprites[i].texture_id == MUMMY_ANGRY_TEXT \
			&& data->sprites[i].distance >= 4.0)
			data->sprites[i].texture_id = MUMMY_CALM_TEXT;
		i++;
	}
	sort_sprites_by_distance(data->sprites, data->sprite_count);
}

void	sort_sprites_by_distance(t_sprite *sprites, int	n)
{
	int			i;
	int			j;
	int			max_index;
	t_sprite	tmp;

	i = 0;
	while (i < n)
	{
		max_index = i;
		j = i + 1;
		while (j < n)
		{
			if (sprites[j].distance > sprites[max_index].distance)
				max_index = j;
			j++;
		}
		if (max_index != i)
		{
			tmp = sprites[i];
			sprites[i] = sprites[max_index];
			sprites[max_index] = tmp;
		}
		i++;
	}
}
