# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 20:41:35 by lsantand          #+#    #+#              #
#    Updated: 2025/11/09 01:35:41 by lsantand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= so_long
FLAGSE			= -fsanitize=address
FLAGS			= -Wextra -Werror -Wall -I -g3

MLXFLAGS		= -Iminilibx-linux -lXext -lX11 -lm -lz

SRCS		=	so_long.c \
					animation.c \
					check.c \
					check_solvability.c \
					utils.c \
					enemy_funct.c \
					imgs.c \
					maps_funct.c \
					render.c \
					move.c
			
DIR_MLX 		= minilibx-linux/
MLX				= $(addprefix $(DIR_MLX), libmlx.a)

DIR_LIBFT		= Libft/
LIBFT			= $(addprefix $(DIR_LIBFT), libft.a)

OBJS 			= ${SRCS:%.c=./build/%.o}

HEADER			= includes/so_long.h

all: 			${NAME}

${NAME}:		${OBJS} ${LIBFT} ${MLX}
				${CC} $^ ${FLAGS} ${MLXFLAGS} -o ${NAME}

./build/%.o:	./sources/%.c ${HEADER}
				@mkdir -p build
				${CC} ${FLAGS} -Iminilibx-linux -c $< -o $@

${MLX}:			FORCE
				make -s -C ${DIR_MLX}

${LIBFT}:		FORCE
				make -s -C ${DIR_LIBFT}

$(NAME_B):			${OBJS_BONUS} ${LIBFT} ${MLX}
				${CC} $^ ${FLAGS} ${MLXFLAGS} -o $(NAME_B)

clean:
				${RM} -r ./build

fclean:			clean
				${RM} ${NAME}
				make -s -C ${DIR_MLX} clean
				make -s -C ${DIR_LIBFT} clean

re:				fclean
				${MAKE} all
			
FORCE:

.PHONY: all clean fclean re FORCE