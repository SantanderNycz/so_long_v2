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

# include <fcntl.h>
/*# include "../Libft/libft.h"*/
# include <math.h>
# include <stdio.h>

// Key macros (defina no so_long.h)
#define ESC_KEY KEY_ESCAPE
#define UP_KEY  KEY_W
#define DOWN_KEY KEY_S
#define LEFT_KEY KEY_A
#define RIGHT_KEY KEY_D
#define SPACE_KEY KEY_SPACE

// Color macros
#define WHITE_COLOR WHITE

typedef struct s_assets
{
	Texture2D	bg_2_1;
	Texture2D	bg_2_2;
	Texture2D	bg_2_3;
	Texture2D	bg_1;
	Texture2D	chest_o;
	Texture2D	chest;
	Texture2D	exit;
	Texture2D	player;
	Texture2D	enemy_0;
	Texture2D	enemy_1;
	Texture2D	enemy_2;
	Texture2D	enemy_3;
	Texture2D	wall_bl;
	Texture2D	wall_br;
	Texture2D	wall_tl;
	Texture2D	wall_tr;
	Texture2D	wall_t;
	Texture2D	wall_b;
	Texture2D	wall_l;
	Texture2D	wall_r;
	Texture2D	wall;
}	t_assets;

typedef struct s_game
{
	int			game_state;
	char		*map;
	int			map_w;
	int			map_h;
	int			move;
	int			collect;
	int			player_pos;
	int			loop_state;
	t_assets	assets;
}	t_game;

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

int		put_image(t_game *game, char c, int x, int y); // atualizada para RayLib
int		fill_win(t_game *game); // atualizada para RayLib
Texture2D	get_wall(t_game *game, int x, int y); // atualizada para RayLib

// ---------------------------------------------------------------- so_long.c --

int		close_program(t_game *game);
int		(int keycode, t_game *game);
void	check_event(t_game *game);

// ------------------------------------------------------------------ utils.c --

int		nb_occurrence(char *str, char c);
int		line_len(char *str);
int		get_ind(int pos, char *map, char directions);
int		find_index(char *map, char to_find);
void	find_x_y(t_game *game, int i, int *x, int *y); // atualizada para RayLib
void key_press(t_game *game);
void update_displayed_move(t_game *game);

#endif

#ifndef RAYLIB_H

# include "raylib.h"
# include <stdlib.h>
# include <stdio.h>

/*
 * Provide a minimal Texture2D definition fallback in case raylib.h
 * isn't available in the include path so the header still compiles.
 * If raylib.h is properly included, RAYLIB_H should be defined and
 * this typedef will be skipped.
 */
typedef struct Texture2D
{
	unsigned int id;
	int width;
	int height;
	int mipmaps;
	int format;
} Texture2D;
#endif