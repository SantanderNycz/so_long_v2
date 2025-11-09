# -----------------------
# Configurações principais
# -----------------------
NAME        = so_long.exe
CC          = gcc
FLAGS       = -Wall -Wextra -Werror -g3

# Caminho do Raylib (ajusta se instalaste em outro local)
RAYLIB_PATH = C:/raylib/raylib/src
RAYLIB_FLAGS = -I$(RAYLIB_PATH) -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm

# -----------------------
# Fontes e objetos
# -----------------------
SRCS = sources/so_long.c \
       sources/animation.c \
       sources/check.c \
       sources/check_solvability.c \
       sources/utils.c \
       sources/enemy_funct.c \
       sources/imgs.c \
       sources/maps_funct.c \
       sources/render.c \
       sources/move.c

OBJS = $(SRCS:sources/%.c=build/%.o)
HEADER = includes/so_long.h

# -----------------------
# Libft
# -----------------------
DIR_LIBFT   = Libft
LIBFT       = $(DIR_LIBFT)/libft.a

# -----------------------
# Regras principais
# -----------------------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) $(RAYLIB_FLAGS) -o $(NAME)

# Compilação dos objetos
build/%.o: sources/%.c $(HEADER)
	@mkdir -p build
	$(CC) $(FLAGS) -I$(RAYLIB_PATH) -Iincludes -c $< -o $@

# Libft
$(LIBFT): FORCE
	$(MAKE) -s -C $(DIR_LIBFT)

# -----------------------
# Limpeza
# -----------------------
clean:
	$(RM) -r build

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s -C $(DIR_LIBFT) clean

re: fclean all

# -----------------------
# Força rebuild
# -----------------------
FORCE:

.PHONY: all clean fclean re FORCE
