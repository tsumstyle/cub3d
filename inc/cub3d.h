/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:16 by aroux             #+#    #+#             */
/*   Updated: 2025/05/13 14:26:44 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# ifndef PI
#  define PI 3.14159265358979323846
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
# define WIDTH 1280
# define HEIGHT 720
# define TEXT_WIDTH	64
# define TEXT_HEIGHT 64

# define MAP_OFFSET_X 10
# define MAP_OFFSET_Y 10
# define MINI_TILE_SIZE 16
# define MINI_PLAYER_SIZE 8
# define MINI_FLOOR_COLOR 0x444444
# define MINI_WALL_COLOR 0xAAAAAA
# define MINI_FOV 60 // Grad
# define MINI_RAY_STEP 2 // Abstand zwischen den Linien
# define MINI_RAY_LENGTH 8 // in Mapfeldern


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
	int		height;
	int		width;
}		t_map;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle; 		// 0605A: added the player's angle (in radians) to facilitate ray casting
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	char	orientation;
}		t_player;

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
	t_gc		*gc_list;
	void		*mlx;
	void		*win;
	t_img		img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			floor_color;
	int			ceiling_color;
	char		*path_wall_n;
	char		*path_wall_s;
	char		*path_wall_w;
	char		*path_wall_e;
	t_img		text_n;
	t_img		text_s;
	t_img		text_w;
	t_img		text_e;
	double		wall_hit_x;
	double		wall_hit_y;
	char		wall_orient;
	int			wall_height;
	t_map		map;
	t_player	player;
}		t_data;

/****************/
/*  PROTOTYPES  */
/****************/
void	data_init(t_data *data);


/**********/
/*  GAME  */
/**********/
/*  game_loop  */
void	run_game(t_data *game);
int		game_loop(t_data *game);
void	launch_window(t_data *data);

/**************/
/*  MOVEMENT  */
/**************/
/*  handle_input  */
int		handle_input(int keysym, t_data *game);

/*  move_basic  */
void	move_forward(t_player *player, char **map);
void	move_backward(t_player *player, char **map);
void	strafe_left(t_player *player, char **map);
void	strafe_right(t_player *player, char **map);

/*  move_rotate  */
void	rotate_left(t_player *player);
void	rotate_right(t_player *player);

/***********/
/*  PARSE  */
/***********/
/* check cmdline args */
int		check_command_line_arguments(int argc, char **argv);

/*  parser  */
void	parser(t_data *data, const char *filename);
int		get_max_line_len(char **map, int n);

/* load cub file */
void	load_cub_file(t_data *data, const char *filename);
void	load_map(t_data *data, int n);
int		count_lines(t_data *data, const char *filename);

/*  check each line  */
int		check_each_line(t_data *data, int n);
int		get_line_type(char *line);
int		is_rgb_number(char **line);
char	*trim_spaces(char *str);

/*  check line is valid  */
int		check_line_is_valid(char *line, int type);
int		check_line_texture(char *line);
int		check_line_floor(char *line);
int		check_line_ceiling(char *line);

/* parse line */
void	parse_line(t_data *data, char *line, int type);
void	parse_line_floor(t_data *data, char *line);
void	parse_line_ceiling(t_data *data, char *line);
void	parse_line_texture(t_data *data, char *line, int type);

/* check map is last */
int		check_map_last(char **file, int n);

/*  check map  */
int		check_map(char **map, int n);
int		check_first_last_row(char **map, int n);
int		check_first_last_col(char **map, int n);
int		check_player(char **map, int n);
int		check_holes(char **map, int n);

/*  init player */
void	init_player(t_data *data, char **map, int n);
void	init_dir_plane_rot_move(t_data *data);
void	init_angle(t_data *data, char **map, int i, int j);

/* init textures and map */
void	init_map_width_height(t_data *data, char **map, int n);
void	init_textures(t_data *data);
void	init_img_struct(t_data *data, t_img *text_img, char *path);

/*  PRINT  */
void	print_cub_file(char **arr);
void	print_parsing_result(t_data *data);

/************/
/*  RENDER  */
/************/
/*  minimap  */
void	draw_minimap(t_data *game);
void	draw_square(t_data *game, int x, int y, int color);
void	draw_minimap_player_and_pov(t_data *game);

/*  minimap FOV */
void	draw_minimap_fov(t_data *game);
void	draw_minimap_ray(t_data *game, double rel_angle);

/*  render  */
int		render_game(t_data *data);
void	cast_ray(t_data *data, int slice);

/* calculate wall distance */
double	calculate_wall_distance(t_data *data, double ray_angle, bool minimap);
void	store_hit_coordinates(t_data *data, double ray_x, double ray_y, \
								double ray_angle);
void	find_wall_orient(t_data *data, double ray_x, double ray_y, \
						double ray_angle);
void	fisheye_correction(t_data *data, double *wall_dist, double ray_angle, \
							bool minimap);

/* draw_slice */
void	draw_slice(t_data *data, int slice, double wall_dist);
void	draw_wall_pixel(t_data *data, int x, int y, int start);
t_img	get_texture(t_data *data);
void	put_pixel_to_image(t_data *data, int x, int y, int color);

/*  draw walls ceiling  */
void	draw_floor_ceiling(t_data *data, int slice, int start, int end);

/***********/
/*  UTILS  */
/***********/
/* cleanup */
int		clean_exit(t_data *game, char *msg);
void	free_img_win_mlx(t_data *data, char *err_msg);
int		handle_close(void *param);
int		close_program(t_data *data, char *msg);
void	free_textures(t_data *data);

char	**split_nl(char const *s, char c);

/* garbage collector */
void	*gc_malloc(t_data *data, size_t size);
void	gc_free_all(t_data *data);
void	gc_free(t_data *data, void *ptr);

/* gc_get_next_line */
char	*gc_gnl(t_data *data, int fd);

/* gc_strtrim */
char	*gc_strtrim(t_data *data, char const *s1, char const *set);

/* gc_strdup */
char	*gc_strdup(t_data *data, const char *s);

#endif