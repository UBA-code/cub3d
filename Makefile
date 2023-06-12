PARSING_PATH= ./src/parsing/
EXECUTION_PATH= ./src/execution/
SRCS = cub3d.c \
		$(PARSING_PATH)utils/utils.c \
		$(PARSING_PATH)utils/ft_swap.c \
		$(PARSING_PATH)utils/dup_tab.c \
		$(PARSING_PATH)utils/ft_exit.c \
		$(PARSING_PATH)utils/tab_free.c \
		$(PARSING_PATH)utils/free_utils.c \
		$(PARSING_PATH)utils/small_join.c \
		$(PARSING_PATH)read_info/get_info.c \
		$(PARSING_PATH)read_info/get_full_file.c \
		$(PARSING_PATH)read_info/get_map.c \
		$(PARSING_PATH)check/check_utils.c \
		$(PARSING_PATH)check/check_map.c \
		$(PARSING_PATH)check/check_map_utils.c \
		$(PARSING_PATH)check/check_info.c \
		$(PARSING_PATH)check/check_colors.c \
		$(PARSING_PATH)draw_map/game.c \
		$(PARSING_PATH)draw_map/render.c \
		$(PARSING_PATH)draw_map/events.c \
		$(PARSING_PATH)draw_map/images.c \
		$(PARSING_PATH)draw_map/raycast.c \
		$(PARSING_PATH)draw_map/walls_draw.c \
		$(PARSING_PATH)draw_map/player.c \
		./src/init/infos.c \
		./src/init/init.c \
		./src/init/ft_split_set.c \

OBJ = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
# CFLAGS += -fsanitize=address -g3
LIBS = libft
# MLX = -Iminilibx/
MLX = -lmlx -framework OpenGL -framework AppKit
NAME = cub3d
OBJDIR=obj

all: $(LIBS) $(NAME)

$(NAME): $(OBJ)
	$(CC) -I src/libft $(CFLAGS) $(OBJ) src/libft/libft.a $(MLX) -lm -o $(NAME)

$(LIBS):
	make -C src/libft

clean:
	rm -rf $(OBJ)
	make -C src/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C src/libft fclean

run:
	rm -rf $(OBJ)
	make $(all)
	./cub3d maps/big.cub

re: fclean all

.PHONY: all clean fclean re run