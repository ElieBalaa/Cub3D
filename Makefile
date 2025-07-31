NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
# Source files
SRC         = main.c
OBJS        = $(SRC:.c=.o)
# Directories
MLX_DIR     = includes/mlx
LIBFT_DIR   = ./libft
# Libraries
MLX         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT       = $(LIBFT_DIR)/libft.a
# Includes
INCLUDES    = -I includes -I $(LIBFT_DIR) -I get_next_line -I $(MLX_DIR)
# Build rules
all: $(NAME)
$(NAME): $(OBJS)
    @make -C $(LIBFT_DIR) > /dev/null
    @make -C $(MLX_DIR) > /dev/null
    @$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
    @echo "\033[1;32m[$(NAME)] created successfully.\033[0m"
%.o: %.c
    @$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
clean:
    @make -C $(LIBFT_DIR) clean > /dev/null
    @make -C $(MLX_DIR) clean > /dev/null
    @rm -f $(OBJS)
    @echo "\033[1;36m[$(NAME)] objects removed.\033[0m"
fclean: clean
    @make -C $(LIBFT_DIR) fclean > /dev/null
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
