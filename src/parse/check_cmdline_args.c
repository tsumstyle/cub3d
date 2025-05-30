/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:34:20 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/19 12:25:05 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_command_line_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		if (argc > 2)
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
