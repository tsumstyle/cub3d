/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:21:55 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/15 16:05:02 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_cub_file(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s", arr[i]);
		i++;
	}
}

void	print_parsing_result(t_data *data)
{
	printf("\nTHE PARSING\n");
	printf("NO texture path: %s\n", data->path_wall_n);
	printf("SO texture path: %s\n", data->path_wall_s);
	printf("WE texture path: %s\n", data->path_wall_w);
	printf("EA texture path: %s\n", data->path_wall_e);
	printf("player_pos_x: %f\n", data->player.x);
	printf("player_pos_y: %f\n", data->player.y);
}
