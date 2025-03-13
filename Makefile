# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 11:17:11 by aroux             #+#    #+#              #
#    Updated: 2025/03/13 15:28:16 by aroux            ###   ########.fr        #
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
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/parse/f_check_command_line_arguments.c \
	$(SRC_DIR)/parse/f_load_map.c \
	$(SRC_DIR)/parse/f_parser.c \
	$(SRC_DIR)/parse/f_print_map.c \
	$(SRC_DIR)/parse/check_map.c \
	$(SRC_DIR)/utils/f_split_nl.c \
	$(SRC_DIR)/utils/gc_get_next_line.c \
	$(SRC_DIR)/utils/gc.c

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_DIRS = obj obj/parse obj/utils

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

# Regel zur Erstellung der Objektdateien
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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/good/library.cub

re: fclean all

.PHONY: all clean fclean re valgrind