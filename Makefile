NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
# Sources
SRC_DIR = srcs/
SRC         = main.c \
	srcs/utils.c \
	srcs/init_game.c \
	srcs/texture_utils.c \
	srcs/game_loop.c \
	srcs/rendering.c \
	srcs/map_parser.c \
	srcs/map_utils.c \
	srcs/map_helpers.c \
	srcs/movement.c \
	srcs/raycasting.c \
	srcs/ray_utils.c \
	srcs/ray_helpers.c \
	srcs/collision.c \
	srcs/minimap.c \
	srcs/window_utils.c \
	srcs/minimap_utils.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
# Directories
MLX_DIR     = minilibx-linux
LIBFT_DIR   = ./libft
GNL_DIR     = ./get_next_line
# Libraries
MLX         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT       = $(LIBFT_DIR)/libft.a
GNL_OBJS    = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o
# Includes
INCLUDES    = -I includes -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)
# Build rules
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@make -C $(GNL_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "\033[1;32m[$(NAME)] created successfully.\033[0m"

# Create obj/ directory and compile .o files inside it
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null
# 	@make -C $(MLX_DIR) clean > /dev/null
	@make -C $(GNL_DIR) clean > /dev/null
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;36m[$(NAME)] objects and obj/ directory removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@make -C $(GNL_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "\033[1;31m[$(NAME)] executables removed.\033[0m"

re: fclean all
	@echo "\033[1;34m[$(NAME)] project rebuilt successfully.\033[0m"

# Leak check with valgrind
leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

qleaks:
	valgrind -q --leak-check=full ./$(NAME)

# Norminette check (adjust the directory as needed)
norm:
	norminette $(SRC) includes/ get_next_line/ libft/ | grep Error || true

.PHONY: all clean fclean re leaks qleaks norm
