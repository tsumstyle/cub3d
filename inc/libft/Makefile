# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:59:42 by aroux             #+#    #+#              #
#    Updated: 2025/03/13 13:07:31 by aroux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I./include
SRC_DIR = src
SRC = 	$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strcmp.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_lstnew.c \
		$(SRC_DIR)/ft_lstadd_front.c \
		$(SRC_DIR)/ft_lstsize.c \
		$(SRC_DIR)/ft_lstlast.c \
		$(SRC_DIR)/ft_lstadd_back.c \
		$(SRC_DIR)/ft_lstdelone.c \
		$(SRC_DIR)/ft_lstclear.c \
		$(SRC_DIR)/ft_lstiter.c \
		$(SRC_DIR)/ft_lstmap.c \
		$(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/ft_printf_utils.c \
# SRC := $(addprefix src/ft_, $(SRC))

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
