/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_each_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:15:30 by aroux             #+#    #+#             */
/*   Updated: 2025/03/24 13:53:48 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check lines: for each line of the file:
	- get line type
	- check that line is valid (except for map lines)
	- retrieve the infos from the line (except for map lines) */
int	check_each_line(t_data *data, int n)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	flag = 0;
	while (i < n)
	{
		if (!data->map.file[i])
			return (1);
		type = get_line_type(data->map.file[i]);
		if (check_line_is_valid(data->map.file[i], type) != 0)
			return (1);
		if (type == L_FLOOR || type == L_CEILING || type == L_TEXT_NO || \
		type == L_TEXT_SO || type == L_TEXT_EA || type == L_TEXT_WE)
			flag++;
		parse_line(data, data->map.file[i], type);
		i++;
	}
	if (flag != 6)
		return (2);
	return (0);
}

int	get_line_type(char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] == '\n')
		return (L_EMPTY);
	if (!line || !line[j] || (line[j] && !line[j + 1]))
		return (L_ERROR);
	if (line[j] == 'F' && line[j + 1] == ' ')
		return (L_FLOOR);
	if (line[j] == 'C' && line[j + 1] == ' ')
		return (L_CEILING);
	if (line[j] == 'N' && line[j + 1] == 'O')
		return (L_TEXT_NO);
	if (line[j] == 'S' && line[j + 1] == 'O')
		return (L_TEXT_SO);
	if (line[j] == 'E' && line[j + 1] == 'A')
		return (L_TEXT_EA);
	if (line[j] == 'W' && line[j + 1] == 'E')
		return (L_TEXT_WE);
	if (line[j] == '1' || line[j] == '0')
		return (L_MAP);
	else
		return (L_ERROR);
}

int	is_rgb_number(char **line)
{
	int		n;
	char	*ptr;

	ptr = *line;
	n = 0;
	if (!ft_isdigit(*ptr))
		return (-1);
	while (ft_isdigit(*ptr))
	{
		n = n * 10 + (*ptr - '0');
		ptr++;
	}
	if (n > 255)
		return (-1);
	*line = ptr;
	return (n);
}

char	*trim_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}
