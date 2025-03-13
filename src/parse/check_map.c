/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:27:32 by aroux             #+#    #+#             */
/*   Updated: 2025/03/13 16:36:48 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(char **map, int n)
{
	int	max_len;

	max_len = get_max_line_len(map, n);
	// check map structure: map in enclosed walls
	// 		checking that first and last lines of the map are '1'
	// 		checking that the first and last char of each map line is 1
	if (check_first_last_row(map, n) != 0 || check_first_last_col(map, n) != 0)
		return (1);
	// check that there is one unique player (one unique occurence of N/S/E/W)
	if (check_player(map, n) != 0)
		return (2);
	// check that there is no empty space next to a '0'
	if (check_holes(map, n) != 0)
		return (3);

	// check and parses colors and textures (see invalid maps)
	//		
	return (0);
}

int	check_first_last_row(char **map, int n)
{
	int	j;

	j = 0;
	while (map[8][j])
	{
		if (map[8][j] != '1')
			return (1);
		j++;
	}
	j = 0;
	while (map[n - 1][j])
	{
		if (map[n - 1][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_first_last_col(char **map, int n)
{
	int	i;
	int	j;

	i = 8;
	while (i < n)
	{
		if (!map[i] || map[i][0] != '1')
			return (1);
		j = 0;
		while (map[i][j])
			j++;
		if (j > 0 && map[i][j - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_player(char **map, int n)
{
	int	i;
	int	j;
	int	player_flag;

	i = 8;
	player_flag = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
				|| map[i][j] == 'W')
				player_flag++;
			j++;
		}
		i++;
	}
	if (player_flag != 1)
		return (1);
	else
		return (0);
}

int	check_holes(char **map, int n)
{
	int	i;
	int	j;

	i = 8;
	while (i < n)
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (map[i][j] == '0') // if found a walkable space
			{
				if (!map[i - 1] || map[i - 1][j] == ' ' || map[i - 1][j] == '\0') // tile up 
					return (1);
				if (!map[i + 1] || map[i + 1][j] == ' ' || map[i + 1][j] == '\0') // tile down
					return (1);
				if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\0')) // tile left
					return (1);
				if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0') // tile right
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}





