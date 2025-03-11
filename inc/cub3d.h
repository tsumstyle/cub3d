/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:16 by aroux             #+#    #+#             */
/*   Updated: 2025/03/11 14:40:02 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

/***************/
/*  LIBRARIES  */
/***************/
# include "minilibx-linux/mlx.h"
# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"
# include "libft/include/get_next_line.h"

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>


/***************/
/* 	 MACROS	   */
/***************/
/* MACROS: general */
# define WIDTH 800
# define HEIGHT 600

/* MACROS: linux keys */
# define ESC XK_Escape
# define C_KEY 0x63
# define PLUS XK_plus
# define PLUS_NUM XK_KP_Add
# define MINUS XK_minus
# define MINUS_NUM XK_KP_Subtract
# define EQUAL XK_equal
# define UP XK_Up
# define DOWN XK_Down
# define RIGHT XK_Right
# define LEFT XK_Left


/****************/
/*  STRUCTURES  */
/****************/
typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}		t_gc;

typedef struct s_map
{
	char	**map;
}		t_map;

typedef struct s_data
{
	t_gc	*gc_list;	// garbage collector
	/* window and mlx vars */
	void	*mlx;
	void	*win;
	void	*img;	// image buffer
	char	*addr; 	// image data address
	int		bpp;	// bits per pixel
	int		line_len;
	int		endian;
	t_map	map;
}		t_data;

/****************/
/*  PROTOTYPES  */
/****************/


void	data_init(t_data *data);

void	hook_events(t_data *data);
int		key_press(int keycode, t_data *data);
int		close_program(t_data *data);

void	free_data(t_data *data);

// draw image
void	put_pixel(t_data *data, int x, int y, int color);
int		render_image(t_data *data);

/*  PARSE  */
int	f_check_command_line_arguments(int argc, char **argv);
int		f_count_lines(const char *filename);
void	load_map(t_data *data, const char *filename);
void	f_parser(t_data *data, const char *filename);

/*  PRINT  */
void	print_char_array(char **arr);

/*  UTILS  */
char	**f_split_nl(char const *s, char c);

// garbage collector
void	*gc_malloc(t_data *data, size_t size);
void	gc_free_all(t_data *data);
void	gc_free(t_data *data, void *ptr);

#endif