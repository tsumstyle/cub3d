/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:33:41 by aroux             #+#    #+#             */
/*   Updated: 2025/03/24 14:34:07 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_last(t_data *data, int n)
{
	int	i;
	int	t;
	int	map_line;
	int	end_of_map;

	i = 0;
	map_line = 0;
	end_of_map = 0;
	while (i < n)
	{
		t = get_line_type(data->map.file[i]);
		if (t == L_MAP || t == L_ERROR)
		{
			if (end_of_map == 1)
				return (3);
			map_line = 1;
		}
		if (t == L_EMPTY && map_line == 1)
			end_of_map = 1;
		if (map_line == 1 && (t == L_FLOOR || t == L_CEILING || t == L_TEXT_NO \
		|| t == L_TEXT_SO || t == L_TEXT_EA || t == L_TEXT_WE))
			return (2);
		i++;
	}
	return (0);
}
