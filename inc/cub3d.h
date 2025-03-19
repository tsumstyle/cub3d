/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:16 by aroux             #+#    #+#             */
/*   Updated: 2025/03/19 14:36:36 by aroux            ###   ########.fr       */
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
# include <stdbool.h>
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
/* garbage collector */
typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}		t_gc;

/* map */
typedef struct s_map
{
	char	**file;
	char	**map;
	int		n_map_lines;
}		t_map;

/* parsing: type of line in the .cub file */
typedef enum t_line
{
	L_EMPTY = 0,
	L_ERROR = 1,
	L_FLOOR = 2,
	L_CEILING = 3,
	L_TEXT_NO = 4,
	L_TEXT_SO = 5,
	L_TEXT_EA = 6,
	L_TEXT_WE = 7,
	L_MAP = 8
}	t_line;

/* data */
typedef struct s_data
{
	t_gc	*gc_list;	// garbage collector
	/* window and mlx vars */
	void	*mlx;
	void	*win;
	void	*img;	// image buffer
	//char	*addr; 	// image data address
	//int		bpp;	// bits per pixel
	int		line_len;
	//int		endian;
	int		floor_color;
	int		ceiling_color;
	char	*no_text_path;
	char	*so_text_path;
	char	*ea_text_path;
	char	*we_text_path;
	t_map	map;
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
/* CHECK CMDLINE ARGS */
int		check_command_line_arguments(int argc, char **argv);

/*  PARSER  */
void	parser(t_data *data, const char *filename);
int		get_max_line_len(char **map, int n);

/* LOAD CUB FILE */
void	load_cub_file(t_data *data, const char *filename);
void	load_map(t_data *data, int n);
int		count_lines(t_data *data, const char *filename);

/*  PRINT  */
void	print_cub_file(char **arr);
void	print_parsing_result(t_data *data);

/*  CHECK EACH LINE  */
int		check_each_line(t_data *data, int n);
int		get_line_type(char *line);
int		is_rgb_number(char **line);
char	*trim_spaces(char *str);

/*  CHECK LINE IS VALID  */
int		check_line_is_valid(char *line, int type);
int		check_line_texture(char *line);
int		check_line_floor(char *line);
int		check_line_ceiling(char *line);

/* PARSE LINE */
void	parse_line(t_data *data, char *line, int type);
void	parse_line_floor(t_data *data, char *line);
void	parse_line_ceiling(t_data *data, char *line);
void	parse_line_texture(t_data *data, char *line, int type);


/*  CHECK MAP  */
int		check_map(char **map, int n);
int		check_first_last_row(char **map, int n);
int		check_first_last_col(char **map, int n);
int		check_player(char **map, int n);
int		check_holes(char **map, int n);


/***********/
/*  UTILS  */
/***********/
char	**split_nl(char const *s, char c);

// garbage collector
void	*gc_malloc(t_data *data, size_t size);
void	gc_free_all(t_data *data);
void	gc_free(t_data *data, void *ptr);

// get_net_line
char	*gc_gnl(t_data *data, int fd);

// gc_strtrim
char	*gc_strtrim(t_data *data, char const *s1, char const *set);

#endif