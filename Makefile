# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 20:36:21 by rkeli             #+#    #+#              #
#    Updated: 2019/08/26 07:08:51 by rkeli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
FLAGS := -Wall -Werror -Wextra -O3
MLX := -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCL
SRCS :=  srcs/main.c \
        srcs/event.c \
        srcs/mouse_event.c \
        srcs/opncl.c \
        srcs/string_output.c \
        srcs/close_open_cl.c \

LIB := -L./libft -lft -lm
INCL := -I include/ -I libft/
CC := gcc
OBJ := $(SRCS:.c=.o)

all: lib $(OBJ) $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INCL)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(LIB) $(OBJ) $(MLX)

lib:
	@make -C libft/

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean
	@make -C libft/ fclean

re: fclean all
