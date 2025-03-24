/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:51:36 by aroux             #+#    #+#             */
/*   Updated: 2025/03/24 11:19:56 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(t_data *data, char *line, int type)
{
	if (type == L_FLOOR)
		parse_line_floor(data, line);
	if (type == L_CEILING)
		parse_line_ceiling(data, line);
	if (type == L_TEXT_NO || type == L_TEXT_SO || type == L_TEXT_EA \
		|| type == L_TEXT_WE)
		parse_line_texture(data, line, type);
}

void	parse_line_floor(t_data *data, char *line)
{
	int	r;
	int	g;
	int	b;

	line = trim_spaces(line);
	line++;
	line = trim_spaces(line);
	r = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	g = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	b = is_rgb_number(&line);
	data->floor_color = (r << 16) | (g << 8) | b;
}

void	parse_line_ceiling(t_data *data, char *line)
{
	int	r;
	int	g;
	int	b;

	line = trim_spaces(line);
	line++;
	line = trim_spaces(line);
	r = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	g = is_rgb_number(&line);
	line++;
	line = trim_spaces(line);
	b = is_rgb_number(&line);
	data->ceiling_color = (r << 16) | (g << 8) | b;
}

void	parse_line_texture(t_data *data, char *line, int type)
{
	char	*trimmed;

	trimmed = gc_strtrim(data, line, " \n");
	trimmed = trimmed + 2;
	trimmed = trim_spaces(trimmed);
	if (type == L_TEXT_NO)
		data->no_text_path = trimmed;
	if (type == L_TEXT_SO)
		data->so_text_path = trimmed;
	if (type == L_TEXT_EA)
		data->ea_text_path = trimmed;
	if (type == L_TEXT_WE)
		data->we_text_path = trimmed;
}
