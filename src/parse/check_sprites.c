/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:24:48 by aroux             #+#    #+#             */
/*   Updated: 2025/05/16 09:43:43 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_sprites(char **map, int n)
{
	if (check_mummy(map, n) != 0)
		return (1);
	if (check_column(map, n) != 0)
		return (1);
	if (check_torch(map, n) != 0)
		return (1);
	return (0);
}

int	check_mummy(char **map, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'M')
			{
				if (!map[i - 1] || map[i - 1][j] == ' ' || !map[i - 1][j])
					return (1);
				if (!map[i + 1] || map[i + 1][j] == ' ' || !map[i + 1][j])
					return (1);
				if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\0'))
					return (1);
				if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_column(char **map, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				if (!map[i - 1] || map[i - 1][j] == ' ' || !map[i - 1][j])
					return (1);
				if (!map[i + 1] || map[i + 1][j] == ' ' || !map[i + 1][j])
					return (1);
				if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\0'))
					return (1);
				if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_torch(char **map, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'T')
			{
				if (!map[i - 1] || map[i - 1][j] == ' ' || !map[i - 1][j])
					return (1);
				if (!map[i + 1] || map[i + 1][j] == ' ' || !map[i + 1][j])
					return (1);
				if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\0'))
					return (1);
				if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
