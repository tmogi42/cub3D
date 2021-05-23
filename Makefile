# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/23 13:42:32 by tmogi             #+#    #+#              #
#    Updated: 2021/05/23 13:42:52 by tmogi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLONE_MLX_TO = minilibx-linux
LIBFT_PATH = libft
MLX_MAKE = $(MAKE) -C $(CLONE_MLX_TO)
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
H_FILE = cub3d.h

NAME			= cub3D

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I.

SRCS			=	bitmap.c calc_sprite.c calc_wall.c check_map.c draw.c error_check.c\
					get_next_line_utils.c get_next_line.c hook_funcs.c init_params.c load_texture.c\
					my_free_libs.c my_library.c set_map_data.c set_map_data_utils.c main.c

OBJS			=	bitmap.o calc_sprite.o calc_wall.o check_map.o draw.o error_check.o\
					get_next_line_utils.o get_next_line.o hook_funcs.o init_params.o load_texture.o\
					my_free_libs.o my_library.o set_map_data.o set_map_data_utils.o main.o

all:			$(NAME)

$(CLONE_MLX_TO):	
				git clone https://github.com/42Paris/minilibx-linux.git $(CLONE_MLX_TO)

$(NAME):		$(CLONE_MLX_TO) $(H_FILE) ${OBJS}
				${MLX_MAKE}
				${LIBFT_MAKE}
				$(CC) -o $(NAME) $(CFLAGS) $(SRCS) -L$(CLONE_MLX_TO) -lmlx -L/usr/include -lXext -lX11 -lm

clean:
				$(MLX_MAKE) clean
				$(LIBFT_MAKE) clean
				rm -f $(OBJS)

fclean:			clean
				$(LIBFT_MAKE) fclean
				rm -f $(NAME)

re:				fclean all

.PHONY: all clean fclean re
