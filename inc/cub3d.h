/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:16 by aroux             #+#    #+#             */
/*   Updated: 2025/03/21 11:05:37 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

/***************/
/*  LIBRARIES  */
/***************/
# include "minilibx-linux/mlx.h"
# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"
# include <fcntl.h>
# include <unistd.h>
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
# define Q_KEY XK_q
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
# define W_KEY XK_w
# define A_KEY XK_a
# define S_KEY XK_s
# define D_KEY XK_d


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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}		t_player;

typedef struct s_data
{
	t_gc		*gc_list;	// garbage collector
	/* window and mlx vars */
	void		*mlx;
	void		*win;
	void		*img;	// image buffer
	//char		*addr; 	// image data address
	//int		bpp;	// bits per pixel
	int			line_len;
	//int		endian;
	t_player	player;
	t_map		map;
}		t_data;

/****************/
/*  PROTOTYPES  */
/****************/


void	data_init(t_data *data);

void	hook_events(t_data *data);
int		key_press(int keycode, t_data *data);
int		close_program(t_data *data, char *msg);

void	free_data(t_data *data);

// draw image
void	put_pixel(t_data *data, int x, int y, int color);
int		render_image(t_data *data);

/***********/
/*  PARSE  */
/***********/
int		f_check_command_line_arguments(int argc, char **argv);
int		f_count_lines(t_data *data, const char *filename);
void	f_load_map(t_data *data, const char *filename);

/*  PARSER  */
void	f_parser(t_data *data, const char *filename);
int		get_max_line_len(char **map, int n);

/*  PRINT  */
void	f_print_map(char **arr);

/*  CHECK MAP  */
int		check_map(char **map, int n);
int		check_first_last_row(char **map, int n);
int		check_first_last_col(char **map, int n);
int		check_player(char **map, int n);
int		check_holes(char **map, int n);


/***********/
/*  UTILS  */
/***********/
char	**f_split_nl(char const *s, char c);

// garbage collector
void	*gc_malloc(t_data *data, size_t size);
void	gc_free_all(t_data *data);
void	gc_free(t_data *data, void *ptr);

// get_net_line
char	*gc_gnl(t_data *data, int fd);

#endif