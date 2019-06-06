# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 20:36:21 by rkeli             #+#    #+#              #
#    Updated: 2019/06/06 22:31:40 by rkeli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FLAGS = -Wall -Werror -Wextra

MLX = -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCL

SRCS =  srcs/main.c \
        srcs/event.c \
        srcs/mouse_event.c \
        srcs/opncl.c \
        srcs/string_output.c \
        srcs/close_open_cl.c \

OBJ = $(SRCS:.c=.o)

LIB = -L./libft -lft -lm

INCL = -I include/ -I libft/

all: lib $(OBJ) $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@ $(INCL)

$(NAME): $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(LIB) $(OBJ) $(MLX)

lib:
	@make -C libft/

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean
	@make -C libft/ fclean

re: fclean all
