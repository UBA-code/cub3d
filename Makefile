# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:18:36 by ybel-hac          #+#    #+#              #
#    Updated: 2023/03/12 17:48:26 by ybel-hac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_PATH= ./src/parsing/
SRCS = cub3d.c \
		$(PARSING_PATH)utils/ft_error.c \
		$(PARSING_PATH)utils/utils.c \
		$(PARSING_PATH)utils/small_join.c \
		$(PARSING_PATH)read_info/get_info.c \
		$(PARSING_PATH)read_info/get_full_file.c \
		$(PARSING_PATH)read_info/get_map.c \
		$(PARSING_PATH)check/check_map.c
OBG = $(SRCS:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -fsanitize=thread -g3
LIBS = libft

NAME = cub3d

all: $(LIBS) $(NAME)

$(NAME): $(OBG)
	$(CC) -I src/libft $(CFLAGS) $(OBG) src/libft/libft.a -o $(NAME)

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