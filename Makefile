# Makefile for Windows (MinGW)
NAME = so_long.exe

# Compilador
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
INCLUDES = -I./includes -I./raylib/include

# Raylib para Windows
RAYLIB_PATH = ./raylib
RAYLIB_INCLUDE = -I$(RAYLIB_PATH)/include
RAYLIB_LIB = -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32

# Diretórios
SRC_DIR = sources
OBJ_DIR = obj

# Arquivos fonte
SRCS =	$(SRC_DIR)/animation.c \
		$(SRC_DIR)/check_solvability.c \
		$(SRC_DIR)/check.c \
		$(SRC_DIR)/enemy_funct.c \
		$(SRC_DIR)/imgs.c \
		$(SRC_DIR)/maps_funct.c \
		$(SRC_DIR)/move.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/so_long.c \
		$(SRC_DIR)/utils.c

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regras
all: $(OBJ_DIR) $(NAME)
	@echo Build complete!

$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo Linking $(NAME)...
	@$(CC) $(OBJS) $(RAYLIB_LIB) -o $(NAME) -Wl,--subsystem,console
	@echo Done!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $<...
	@$(CC) $(CFLAGS) $(INCLUDES) $(RAYLIB_INCLUDE) -c $< -o $@

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@echo Cleaned object files

fclean: clean
	@if exist $(NAME) del /q $(NAME)
	@echo Removed executable

re: fclean all

run: all
	@$(NAME) maps\level1.ber

.PHONY: all clean fclean re run