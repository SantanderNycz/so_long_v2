# Nome do executável
NAME = so_long

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes

# Raylib
RAYLIB_FLAGS = -lraylib -lm

# Sistema operacional
UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	RAYLIB_FLAGS += -lGL -lpthread -ldl -lrt -lX11
endif

ifeq ($(UNAME), Darwin)
	RAYLIB_FLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
endif

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos fonte
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/game.c \
       $(SRC_DIR)/map.c \
       $(SRC_DIR)/player.c \
       $(SRC_DIR)/enemy.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/input.c \
       $(SRC_DIR)/timer.c

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Cores
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(RAYLIB_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) maps/level1.ber

.PHONY: all clean fclean re run