/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:51:36 by aroux             #+#    #+#             */
/*   Updated: 2025/05/15 16:04:44 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(t_data *data, char *line, int type)
{
	if (type == L_FLOOR)
		data->floor_color = parse_line_floor_or_ceiling(data, line);
	if (type == L_CEILING)
		data->ceiling_color = parse_line_floor_or_ceiling(data, line);
	if (type == L_TEXT_NO || type == L_TEXT_SO || type == L_TEXT_EA \
		|| type == L_TEXT_WE)
		parse_line_texture(data, line, type);
}

unsigned char	*parse_line_floor_or_ceiling(t_data *data, char *line)
{
	unsigned char	*color;

	color = gc_malloc(data, 3 * sizeof(unsigned char));
	if (!color)
		return (NULL);
	line = trim_spaces(line);
	if (*line == 'F' || *line == 'C')
		line++;
	line = trim_spaces(line);
	color[2] = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	color[1] = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	color[0] = is_rgb_number(&line);
	return (color);
}

void	parse_line_texture(t_data *data, char *line, int type)
{
	char	*trimmed;

	trimmed = gc_strtrim(data, line, " \n");
	trimmed = trimmed + 2;
	trimmed = trim_spaces(trimmed);
	if (type == L_TEXT_NO)
		data->path_wall_n = trimmed;
	if (type == L_TEXT_SO)
		data->path_wall_s = trimmed;
	if (type == L_TEXT_EA)
		data->path_wall_e = trimmed;
	if (type == L_TEXT_WE)
		data->path_wall_w = trimmed;
}
