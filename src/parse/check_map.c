/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:27:32 by aroux             #+#    #+#             */
/*   Updated: 2025/03/19 15:59:14 by aroux            ###   ########.fr       */
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
	// BERNIE's suggestion: just check that 0 is surrounded by 1, 0, S/W/N/E; or just check that there is no space and no \n next to it
	if (check_first_last_row(map, n) != 0 || check_first_last_col(map, n) != 0)
		return (1);
	// check that there is one unique player (one unique occurence of N/S/E/W)
	if (check_player(map, n) != 0)
		return (2);
	// check that there is no empty space next to a '0'
	if (check_holes(map, n) != 0)
		return (3);
	return (0);
}

int	check_first_last_row(char **map, int n)
{
	int	j;

	j = 0;
	while (map[0][j] && map[0][j] != '\n')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (1);
		j++;
	}
	j = 0;
	while (map[n - 1][j] && map[n - 1][j] != '\n')
	{
		if (map[n - 1][j] != '1' && map[n - 1][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_first_last_col(char **map, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
			j++;
		if (!map[i][j] || map[i][j] != '1')
			return (1);
		while (map[i][j])
			j++;
		j--;
		while (j > 0 && (map[i][j] == ' ' || map[i][j] == '\t' \
			|| map[i][j] == '\n'))
			j--;
		if (j > 0 && map[i][j] != '1')
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

	i = 0;
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

	i = 0;
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
