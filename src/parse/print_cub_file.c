/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:21:55 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/05 17:06:56 by bbierman         ###   ########.fr       */
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
	printf("floor color: %d\n", data->floor_color);
	printf("ceiling color: %d\n", data->ceiling_color);
	printf("NO texture path: %s\n", data->no_text_path);
	printf("SO texture path: %s\n", data->so_text_path);
	printf("WE texture path: %s\n", data->we_text_path);
	printf("EA texture path: %s\n", data->ea_text_path);
	printf("player_pos_x: %f\n", data->player.x);
	printf("player_pos_y: %f\n", data->player.y);
}
