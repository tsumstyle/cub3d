/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:20 by aroux             #+#    #+#             */
/*   Updated: 2025/05/15 16:34:32 by aroux            ###   ########.fr       */
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
	launch_window(&data); // 0705A: we have two functions that achieve the same thing and I'm not sure why: launch_window and open_window; I changed launch_window so it's cleaner and only 25 lines
	mlx_loop_hook(data.mlx, game_loop, &data);
	run_game(&data);
	return (0);
}

void	data_init(t_data *data)
{
	ft_bzero(data, sizeof(*data));
	data->line_len = WIDTH;
	data->z_buffer = gc_malloc(data, sizeof(double) * WIDTH);
	if (!data->z_buffer)
		clean_exit(data, "Failed to allocate z_buffer\n");
}
