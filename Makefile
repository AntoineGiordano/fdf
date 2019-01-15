# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/10 17:21:00 by agiordan     #+#   ##    ##    #+#        #
#    Updated: 2018/11/25 04:58:35 by agiordan    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fdf

SRC =	fdf.c \
		parse.c \
		ft_put_line.c \
		draw.c \
		hook.c \
		parallele.c
OBJ = $(SRC:%.c=%.o)

COMPIL = gcc
FLAG = -Wall -Werror -Wextra

LIBFT = libft
MLX = minilibx_macos
LIB_MLX = libmlx
INCLUDE = $(LIBFT)/$(LIBFT).a $(MLX)/$(LIB_MLX).a

FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		make -C $(MLX)
		$(COMPIL) $(FLAG) $(OBJ) $(FRAMEWORK) $(INCLUDE) -o $(NAME)

clean:
		rm -f $(OBJ)
		make clean -C $(LIBFT)
		make clean -C $(MLX)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)
		make fclean -C $(MLX)

re: fclean all
