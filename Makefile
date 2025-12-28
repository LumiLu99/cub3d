# Colors
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
PINK 	=	\033[35m
RESET	=	\033[0m

# Program name
NAME = cub3D

# Directories
SRC_DIR = src
PARSING_DIR = parsing
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC = -I$(INC_DIR)
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# Compiler & flags
CC = gcc
CFLAGS = -O3 # -Wall -Werror -Wextra
RM = rm -rf

# Source files
SRC = $(addprefix $(SRC_DIR)/, main.c utils.c key.c player.c raycasting.c texture.c) \
		$(addprefix $(SRC_DIR)/$(PARSING_DIR)/, parse_texture.c parse_map.c parse_color.c parsing_utils.c)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Build rules
all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT): FORCE
	@echo "$(PINK)$(BOLD)=======================================$(RESET)"
	@echo "$(CYAN)  🚀 Building libft...$(RESET)"
	@echo "$(PINK)$(BOLD)=======================================$(RESET)"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSING_DIR)
	@$(CC) $(CFLAGS) $(INC) -Imlx -O3 -c $< -o $@
	@echo "$(YELLOW)Compiled ✅ $(GREEN) $(BOLD) $< $(RESET)"

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx -lXext -lX11 -lm -lz
	@echo "$(GREEN)$(BOLD)✅ Build Successful: $(NAME)$(RESET)"

# Build library folder
$(MLX_LIB): FORCE
	@echo "$(PINK)$(BOLD)=======================================$(RESET)"
	@echo "$(CYAN)  🚀 Building MLX...$(RESET)"
	@echo "$(PINK)$(BOLD)=======================================$(RESET)"
	@make -C $(MLX_DIR)

$(OBJ_DIR): FORCE
	@mkdir -p $(OBJ_DIR)


# Clean object files and executable
clean:
	@echo "$(RED)❌ Deleting\t$(RESET)$(WHITE)Objects$(RESET)\t$(OBJB_DIR)";
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)Objects$(RESET)"

fclean: clean
	@echo "$(RED)❌ Deleting libraries$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)❌ Deleting$(RESET)\t$(NAME)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)$(NAME)$(RESET)"

re: fclean all

# debug:
#	@echo "SRC: $(SRC)"
#	@echo "OBJ: $(OBJ)"
#	@echo "OBJ_DIR: $(OBJ_DIR)"

FORCE:

.PHONY: bonus all clean fclean re

# -I(include directory) - Tells the compiler to look for header files
# -L(directory) - Tells the compiler to look for .a library path in this folder
# -l(%.a) - Tells the compiler to look for that specified .a file
