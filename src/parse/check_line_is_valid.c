/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_is_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:43:18 by aroux             #+#    #+#             */
/*   Updated: 2025/05/14 16:55:35 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_is_valid(char *line, int type)
{
	int	errno;

	errno = 0;
	if (type == L_FLOOR)
		errno = check_line_floor(line);
	if (type == L_CEILING)
		errno = check_line_ceiling(line);
	if (type == L_TEXT_NO || type == L_TEXT_SO || type == L_TEXT_EA \
		|| type == L_TEXT_WE)
		errno = check_line_texture(line);
	return (errno);
}

int	check_line_texture(char *line)
{
	line = trim_spaces(line);
	line = line + 2;
	if (*line != ' ')
		return (1);
	line++;
	while (*line)
		line++;
	line--;
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line--;
	if (ft_strncmp(line - 3, ".xpm", 4) != 0)
		return (1);
	return (0);
}

int	check_line_floor(char *line)
{
	line = trim_spaces(line);
	line++;
	if (!*line || *line != ' ')
		return (1);
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	if (*line != ',')
		return (1);
	line++;
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	if (*line != ',')
		return (1);
	line++;
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	line = trim_spaces(line);
	if (*line == '\n')
		line++;
	if (*line != '\0')
		return (1);
	return (0);
}

int	check_line_ceiling(char *line)
{
	line = trim_spaces(line);
	line++;
	if (!*line || *line != ' ')
		return (1);
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	if (*line != ',')
		return (1);
	line++;
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	if (*line != ',')
		return (1);
	line++;
	line = trim_spaces(line);
	if (is_rgb_number(&line) == RGB_ERR)
		return (1);
	line = trim_spaces(line);
	if (*line == '\n')
		line++;
	if (*line != '\0')
		return (1);
	return (0);
}
