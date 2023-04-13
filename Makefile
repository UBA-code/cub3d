# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:18:36 by ybel-hac          #+#    #+#              #
#    Updated: 2023/04/13 15:29:59 by ybel-hac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_PATH= ./src/parsing/
EXECUTION_PATH= ./src/execution/
SRCS = cub3d.c \
		$(PARSING_PATH)utils/ft_error.c \
		$(PARSING_PATH)utils/utils.c \
		$(PARSING_PATH)utils/ft_swap.c \
		$(PARSING_PATH)utils/dup_tab.c \
		$(PARSING_PATH)utils/tab_free.c \
		$(PARSING_PATH)utils/free_utils.c \
		$(PARSING_PATH)utils/small_join.c \
		$(PARSING_PATH)read_info/get_info.c \
		$(PARSING_PATH)read_info/get_full_file.c \
		$(PARSING_PATH)read_info/get_map.c \
		$(PARSING_PATH)check/check_map.c \
		$(PARSING_PATH)check/check_map_utils.c \
		$(PARSING_PATH)check/check_info.c \
		$(PARSING_PATH)check/check_colors.c
OBG = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CFLAGS = -fsanitize=address
LIBS = libft
# MLX = -Iminilibx/
MLX = -lX11 -lXext -lmlx
NAME = cub3d
OBJDIR=obj

all: $(LIBS) $(NAME)

$(NAME): $(OBG)
	$(CC) -I src/libft $(CFLAGS) $(OBG) src/libft/libft.a $(MLX) -o $(NAME)

$(LIBS):
	make -C src/libft

clean:
	rm -rf $(OBG)
	make -C src/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C src/libft fclean

re: fclean all

.PHONY: all clean fclean re