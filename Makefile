# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emende <emende@student.42.fr>              +#+  +:+       +#+         #
:#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 12:46:17 by emende            #+#    #+#              #
#    Updated: 2022/03/27 18:39:18 by emende           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = -I libft/includes -L libft -lft
MLX = -I /usr/local/include -L /usr/local/lib -lmlx
FRAMEWORKS = -framework OpenGL -framework AppKit
OBJS = main.o ft_mlx_pixel_put.o draw_line.o hook_key.o free_arrays.o \
	   read_values.o draw_projection.o images.o color.o

all:  $(NAME)

%.o: %.c Makefile fdf.h
	$(CC) $(CFLAGS) -I libft/includes -c $< -o $@

$(NAME): $(OBJS)
	make -C libft/
	$(CC) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(CFLAGS) $(FRAMEWORKS)

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
