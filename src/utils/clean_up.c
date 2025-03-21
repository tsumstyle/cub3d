/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:05:33 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/21 17:11:18 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_program(t_data *data, char *msg)
{
	if (msg)
		printf("%s\n", msg);
	free_data(data); //free whatever we need to before exiting. Garbage collector?
	gc_free_all(data);
	exit(0);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->img.ptr)
	{
		mlx_destroy_image(data->mlx, data->img.ptr);
		data->img.ptr = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}