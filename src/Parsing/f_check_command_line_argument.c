/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check_command_line_argument.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:34:20 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/10 16:43:24 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	f_check_command_line_argument(int argc, char **argv, t_data *data)
{
	if (argc > 3)
		ft_exit(data, "Error\nToo many commandline arguments\n");
	if (argc < 2)
		ft_exit(data, "Error\nToo few commandline arguments\n");
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		ft_exit(data, "Error\nSorry, no .cub-file\n");
}
