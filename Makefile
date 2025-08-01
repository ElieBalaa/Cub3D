NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
# Source files
SRC         = main.c \
              srcs/utils.c \
			  srcs/load_map.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
# Directories
MLX_DIR     = includes/mlx
LIBFT_DIR   = ./libft
GNL_DIR		= ./get_next_line
# Libraries
MLX         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT       = $(LIBFT_DIR)/libft.a
GNL       = $(GNL_DIR)/libgnl.a

# Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Build rules
all: $(NAME)

# Update your $(NAME) rule to link GNL
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@make -C $(GNL_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(MLX) -o $(NAME)

# Create subdirectories in obj/ and compile .o files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;36m[$(NAME)] objects and obj/ directory removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "\033[1;31m[$(NAME)] executables removed.\033[0m"

re: fclean all
	@echo "\033[1;34m[$(NAME)] project rebuilt successfully.\033[0m"

# Leak check with valgrind
leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) map.cub

qleaks:
	valgrind -q --leak-check=full ./$(NAME)

# Norminette check
norm:
	norminette $(SRC) includes/ get_next_line/ libft/ | grep Error || true

.PHONY: all clean fclean re leaks qleaks norm
