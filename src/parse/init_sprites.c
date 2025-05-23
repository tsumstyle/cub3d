/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:53:32 by aroux             #+#    #+#             */
/*   Updated: 2025/05/16 10:06:57 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprites(t_data *data, char **map, int n)
{
	int	i;
	int	j;

	data->sprite_count = 0;
	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'M' || map[i][j] == 'C')
			{
				data->sprites[data->sprite_count].x = j + 0.5;
				data->sprites[data->sprite_count].y = i + 0.5;
				set_texture_id(data, map[i][j]);
				data->sprite_count++;
				if (data->sprite_count >= MAX_SPRITES)
					return ;
			}
			j++;
		}
		i++;
	}
}

void	set_texture_id(t_data *data, char c)
{
	if (c == 'M')
		data->sprites[data->sprite_count].texture_id = MUMMY_CALM_TEXT;
	if (c == 'C')
		data->sprites[data->sprite_count].texture_id = COLUMN_TEXT;
	if (c == 'T')
		data->sprites[data->sprite_count].texture_id = TORCH_TEXT_1;
}

void	init_sprite_textures(t_data *data)
{
	data->textures[MUMMY_CALM_TEXT] = ft_load_xpm(data, "./textures/egypt/mummy_1.xpm");
	data->textures[MUMMY_ANGRY_TEXT] = ft_load_xpm(data, "./textures/egypt/mummy_2.xpm");
	data->textures[COLUMN_TEXT] = ft_load_xpm(data, "./textures/egypt/column.xpm");
	data->textures[TORCH_TEXT_1] = ft_load_xpm(data, "./textures/egypt/torch_1.xpm");
	data->textures[TORCH_TEXT_2] = ft_load_xpm(data, "./textures/egypt/torch_2.xpm");

	if (!data->textures[MUMMY_CALM_TEXT].ptr)
		clean_exit(data, "Error. Failed to load mummy calm textures.\n");
	if (!data->textures[MUMMY_ANGRY_TEXT].ptr)
		clean_exit(data, "Error. Failed to load mummy angry textures.\n");
	if (!data->textures[COLUMN_TEXT].ptr)
		clean_exit(data, "Error. Failed to load column textures.\n");
	if (!data->textures[TORCH_TEXT_1].ptr)
		clean_exit(data, "Error. Failed to load torch1 textures.\n");
	if (!data->textures[TORCH_TEXT_2].ptr)
		clean_exit(data, "Error. Failed to load torch2 textures.\n");
}

t_img	ft_load_xpm(t_data *data, const char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(data->mlx, (char *)path, &img.line_len, &img.bpp);
	if (!img.ptr)
		return ((t_img){0});
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}
