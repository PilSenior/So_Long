NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes

LIBFT = libft/libft.a
PRINTF = ft_printf/printf.a
MLX = minilibx/libmlx.a

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/draw_map.c \
       $(SRC_DIR)/map.c \
       $(SRC_DIR)/map2.c \
       $(SRC_DIR)/handle_input.c \
       $(SRC_DIR)/player_movement.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/free.c \
       $(SRC_DIR)/floot_fill.c \
       $(SRC_DIR)/get_next_line.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -I ft_printf -I minilibx -c $< -o $@

all: $(LIBFT) $(PRINTF) $(MLX) $(NAME)

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C ft_printf

$(MLX):
	make -C minilibx

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(MLX) -L minilibx -lmlx -lm -lX11 -lXext -o $(NAME)

clean:
	make -C libft clean  
	make -C ft_printf clean 
	rm -rf $(OBJ_DIR)
	

fclean: clean
	make -C libft fclean 
	make -C ft_printf fclean
	make  -C minilibx clean  
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
