/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check_command_line_argument.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:34:20 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/11 14:39:34 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	f_check_command_line_arguments(int argc, char **argv)
{
	if (argc != 3)
	{
		if (argc > 3)
			ft_printf("Error\nToo many commandline arguments\n");
		if (argc < 2)
			ft_printf("Error\nToo few commandline arguments\n");
		return (1);
	}
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		ft_printf("Error\nSorry, no .cub-file\n");
		return (2);
	}
	return (0);
}
