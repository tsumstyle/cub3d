/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/05/15 16:03:12 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_command_line_arguments(argc, argv) != 0)
		return (1);
	data_init(&data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		perror("Malloc failed");
		exit (1);
	}
	parser(&data, argv[1]);
	launch_window(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	run_game(&data);
	return (0);
}

void	data_init(t_data *data)
{
	ft_bzero(data, sizeof(*data));
	data->line_len = WIDTH;
}
