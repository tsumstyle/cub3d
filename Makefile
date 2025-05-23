# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 11:17:11 by aroux             #+#    #+#              #
#    Updated: 2025/05/16 10:53:30 by aroux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -Iinc -I$(MLX_DIR)
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = inc/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -lm	#external libraries

SRC_DIR = src
SRC = src/main.c \
	src/game/game_loop.c \
	src/movement/handle_input.c		src/movement/move_basic.c   src/movement/move_rotate.c \
	src/parse/check_cmdline_args.c	src/parse/load_cub_file.c   src/parse/parser.c \
	src/parse/print_cub_file.c		src/parse/check_each_line.c src/parse/check_line_is_valid.c \
	src/parse/check_map_last.c		src/parse/check_map.c       src/parse/parse_line.c      \
	src/parse/init_player.c 		src/parse/init_textures_and_map.c \
	src/parse/check_sprites.c		src/parse/init_sprites.c \
	src/render/minimap.c			src/render/minimap_fov.c	src/render/render.c			\
	src/render/calculate_wall_distance.c	src/render/fog.c	src/render/draw_slice.c	\
	src/render/draw_floor_ceiling.c	src/render/update_sprites.c	src/render/draw_sprites.c \
	src/utils/clean_up.c			src/utils/split_nl.c 		src/utils/gc_get_next_line.c \
	src/utils/gc_strtrim.c 			src/utils/gc.c				src/utils/gc_strdup.c

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_DIRS = obj obj/parse obj/utils

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/parse $(OBJ_DIR)/utils
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(OBJ_DIRS):
	@mkdir -p $@
	@echo "Creating directory: $@"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

valgrind:
	valgrind --leak-check=full \
	./$(NAME) maps/good/egypt.cub

valfull:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	./$(NAME) maps/good/egypt.cub

re: fclean all

.PHONY: all clean fclean re valgrind