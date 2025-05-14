/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:05:33 by bbierman          #+#    #+#             */
/*   Updated: 2025/05/14 13:09:32 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_exit(t_data *game, char *msg)
{
	printf("Exit before lauching game...\n");
	if (msg)
		printf("%s\n", msg);
	free_textures(game);
	gc_free_all(game);
	exit(0);
	return (0);
}

int	handle_close(void *param)
{
	t_data	*game;

	game = (t_data *)param;
	return (close_program(game, "Window closed"));
}

int	close_program(t_data *game, char *msg)
{
	printf("Closing program...\n");
	free_textures(game);
	free_img_win_mlx(game, msg);
	gc_free_all(game);
	exit(0);
	return (0);
}

void	free_img_win_mlx(t_data *data, char *err_msg)
{
	int	i;

	i = 0;
	if (!data)
		return ;
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
	if (err_msg)
		printf("%s", err_msg);
}

void	free_textures(t_data *data)
{
	if (data->text_n.ptr)
		mlx_destroy_image(data->mlx, data->text_n.ptr);
	if (data->text_s.ptr)
		mlx_destroy_image(data->mlx, data->text_s.ptr);
	if (data->text_e.ptr)
		mlx_destroy_image(data->mlx, data->text_e.ptr);
	if (data->text_w.ptr)
		mlx_destroy_image(data->mlx, data->text_w.ptr);
}
