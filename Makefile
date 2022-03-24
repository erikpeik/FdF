# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emende <emende@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 12:46:17 by emende            #+#    #+#              #
#    Updated: 2022/03/24 16:07:04 by emende           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CPPFLAGS = -I libft/includes -L libft -lft
MLX_INCL = -I /usr/local/include -L /usr/local/lib -lmlx
FRAMEWORKS = -framework OpenGL -framework AppKit
OBJS = main.o

all:  $(NAME)

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
