/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:44:23 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/26 18:37:31 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ER_NAME "O nome fornecido como parametro está incorreto.\n"
# define ER_NOMAP "O mapa não pode ser carregado.\n"
# define ER_MAPCHAR "O mapa contém caracteres inválidos.\n"
# define ER_NOSTART "O mapa deve conter uma posicao de partida\n"
# define ER_NOEND "O mapa deve conter uma saída.\n"
# define ER_NOCOL "O mapa deve conter ao menos um coletável.\n"
# define ER_MAPLEN "Todas as linhas do mapa deve ter o mesmo comprimento.\n"
# define ER_WALL "O mapa deve ser fechado por paredes em todos os lados.\n"
# define ER_RESOLVE "O mapa não pode ser resolvido.\n"
# define WARN_NO_ENEMY "O mapa pode não ter inimigo, mas será iniciado.\n"
# define WIN "Você ganhou, mizerávi!\n"
# define DEATH "Morreu, abestado!\n"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"
# include <math.h>
# include <stdio.h>

typedef struct s_assets
{
	void	*bg_2_1;
	void	*bg_2_2;
	void	*bg_2_3;
	void	*bg_1;
	void	*chest_o;
	void	*chest;
	void	*exit;
	void	*player;
	void	*enemy_0;
	void	*enemy_1;
	void	*enemy_2;
	void	*enemy_3;
	void	*wall_bl;
	void	*wall_br;
	void	*wall_tl;
	void	*wall_tr;
	void	*wall_t;
	void	*wall_b;
	void	*wall_l;
	void	*wall_r;
	void	*wall;
}				t_assets;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	int			game_state;
	char		*map;
	int			map_w;
	int			map_h;
	int			move;
	int			collect;
	int			player_pos;
	int			loop_state;
	t_assets	assets;
}				t_game;

// -------------------------------------------------------------- animation.c --

int		anime_enemy(t_game *game, int anim_state);
int		loop_animations(t_game *game);

// ------------------------------------------------------ check_solvability.c --

char	*spread(char *mapcpy, int pos, int *nb_to_find);
int		check_map_can_be_solved(char *map, t_game *game);

// ------------------------------------------------------------------ check.c --

int		check_enclosure(char *map);
int		check_charactere(char *map);
int		check_integrity(char *map);
int		check_map(t_game *game, char *filename);

// ------------------------------------------------------------ enemy_funct.c --

int		enemy_can_be_place(int i, char *m);
int		add_enemy(t_game *game);
char	*move_enemy(t_game *game, int from, char state, char *map_cpy);
int		change_enemys_pos(t_game *game);

// ------------------------------------------------------------------- imgs.c --

int		open_imgs(void *mlx, t_game *game);
int		close_img(t_game *g);
int		close_img_wall(t_game *g);

// ------------------------------------------------------------- maps_funct.c --

int		get_map_size(t_game *game, char *filename);
int		get_map(t_game *game, char *file);

// ------------------------------------------------------------------- move.c --

int		move_check(t_game *game, char direction);
int		update_diplayed_move(t_game *game);
int		move_player_set_datas(t_game *game, int from_pos, int x, int y);
int		update_x_y(char direction, int i, int *x, int *y);
int		move_player(t_game *game, int from_pos, char direction);

// ----------------------------------------------------------------- render.c --

int		put_image(t_game game, char c, int x, int y);
int		fill_win(t_game game);
void	*get_wall(t_game game, int x, int y);

// ---------------------------------------------------------------- so_long.c --

int		close_program(t_game *game);
int		key_press(int keycode, t_game *game);
void	check_event(t_game *game);

// ------------------------------------------------------------------ utils.c --

int		nb_occurrence(char *str, char c);
int		line_len(char *str);
int		get_ind(int pos, char *map, char directions);
int		find_index(char *map, char to_find);
int		find_x_y(t_game game, int pos, int *x, int *y);

#endif
