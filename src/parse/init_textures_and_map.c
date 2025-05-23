/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_and_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:11:32 by aroux             #+#    #+#             */
/*   Updated: 2025/05/14 14:13:42 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	init_img_struct(data, &data->text_n, data->path_wall_n);
	init_img_struct(data, &data->text_s, data->path_wall_s);
	init_img_struct(data, &data->text_e, data->path_wall_e);
	init_img_struct(data, &data->text_w, data->path_wall_w);
	init_sprite_textures(data);
}

void	init_img_struct(t_data *data, t_img *text_img, char *path)
{
	int		width;
	int		height;

	text_img->endian = data->img.endian;
	text_img->bpp = data->img.bpp;
	text_img->line_len = data->img.line_len;
	width = TEXT_WIDTH;
	height = TEXT_HEIGHT;
	text_img->ptr = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!text_img->ptr)
		clean_exit(data, "Error. Failed to load texture image\n");
	text_img->addr = mlx_get_data_addr(text_img->ptr, &text_img->bpp, \
	&text_img->line_len, &text_img->endian);
}

void	init_map_width_height(t_data *data, char **map, int n)
{
	int	i;
	int	line_len;
	int	max_width;

	i = 0;
	data->map.height = n;
	max_width = 0;
	while (i < n)
	{
		line_len = 0;
		while (map[i][line_len] != '\0' && map[i][line_len] != '\n')
			line_len++;
		if (line_len >= max_width)
			max_width = line_len;
		i++;
	}
	data->map.width = max_width;
}

