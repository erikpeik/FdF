# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emende <emende@student.42.fr>              +#+  +:+       +#+         #
:#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 12:46:17 by emende            #+#    #+#              #
#    Updated: 2022/03/26 21:51:19 by emende           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I libft/includes -L libft -lft
MLX_INCL = -I minilibx -L minilibx -lmlx
MLX_SCHOOL = -I /usr/local/include -L /usr/local/lib -lmlx
MLX_MAC = -I mlx -Lmlx -lmlx
FRAMEWORKS = -framework OpenGL -framework AppKit
#SRCS_DIR = srcs/
#SCRS_LIST = main.c
#SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = main.o ft_mlx_pixel_put.o

all:  $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I libft/includes -c $< -o $@

$(NAME): $(OBJS)
	make -C libft/
	$(CC) -o $(NAME) $(OBJS) $(MLX_INCL) $(LIBFT_INCL) $(FRAMEWORKS)

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
