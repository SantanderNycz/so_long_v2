#ifndef SO_LONG_H
#define SO_LONG_H

// Includes do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Raylib DEVE ser incluído ANTES de windows.h para evitar conflitos
#include <raylib.h>

// Define para Windows (depois do raylib para evitar conflitos)
#if defined(_WIN32)
    #define PATH_SEPARATOR '\\'
#else
    #define PATH_SEPARATOR '/'
#endif

// Constantes
#define TILE_SIZE 64
#define MAX_LEVELS 10
#define MAX_ENEMIES 50
#define PLAYER_SPEED 4
#define ENEMY_SPEED 2
#define ANIMATION_FRAMES 4
#define ANIMATION_SPEED 0.1f
#define ENEMY_ANIMATION_FRAMES 3
#define COLLECTIBLE_ANIMATION_FRAMES 3

// Tipos de tiles
typedef enum {
    TILE_EMPTY = '0',
    TILE_WALL = '1',
    TILE_PLAYER = 'P',
    TILE_COLLECTIBLE = 'C',
    TILE_EXIT = 'E',
    TILE_ENEMY = 'X'
} TileType;

// Estados do jogo
typedef enum {
    GAME_MENU,
    GAME_PLAYING,
    GAME_WIN,
    GAME_OVER
} GameState;

// Estrutura de posição
typedef struct s_position {
    int x;
    int y;
} t_position;

// Estrutura de animação
typedef struct s_animation {
    Texture2D frames[ANIMATION_FRAMES];
    int currentFrame;
    float frameTimer;
    float frameSpeed;
} t_animation;

// Estrutura do jogador
typedef struct s_player {
    t_position pos;
    t_position startPos;
    int collectibles;
    int moves;
    t_animation animation;
    int direction; // 0=down, 1=up, 2=left, 3=right
} t_player;

// Estrutura do inimigo
typedef struct s_enemy {
    t_position pos;
    t_position startPos;
    t_position target;
    bool active;
    float moveTimer;
    t_animation animation;
    int direction;
} t_enemy;

// Estrutura do mapa
typedef struct s_map {
    char **grid;
    int width;
    int height;
    int totalCollectibles;
    char *filename;
    bool isValid;
    bool isSolvable;
} t_map;

// Estrutura do timer
typedef struct s_timer {
    double startTime;
    double elapsedTime;
    bool running;
} t_timer;

// Estrutura de texturas
typedef struct s_textures {
    Texture2D wall;
    Texture2D floor;
    Texture2D collectible;
    Texture2D exit_closed;
    Texture2D exit_open;
    Texture2D player[ANIMATION_FRAMES];
    Texture2D enemy[ANIMATION_FRAMES];
} t_textures;

// Estrutura principal do jogo
typedef struct s_game {
    t_map map;
    t_player player;
    t_enemy *enemies;
    int enemyCount;
    GameState state;
    t_timer timer;
    int currentLevel;
    char *levelFiles[MAX_LEVELS];
    int totalLevels;
    t_textures textures;
    bool exitOpen;
    Font font;
} t_game;

// ==================== FUNÇÕES DE MAPA (maps_function.c) ====================
bool    map_load(t_map *map, const char *filename);
void    map_free(t_map *map);
char    map_get_tile(t_map *map, int x, int y);
void    map_set_tile(t_map *map, int x, int y, char tile);
int     map_count_collectibles(t_map *map);
void    map_print(t_map *map);

// ==================== FUNÇÕES DE VALIDAÇÃO (check.c) ====================
bool    check_map_valid(t_map *map);
bool    check_rectangular(t_map *map);
bool    check_walls(t_map *map);
bool    check_elements(t_map *map);
bool    check_characters(t_map *map);

// ==================== FUNÇÕES DE SOLVABILITY (check_solvability.c) ====================
bool    check_solvability(t_map *map);
bool    flood_fill_check(t_map *map, int x, int y, bool **visited, int *collectibles, bool *foundExit);
void    free_visited(bool **visited, int height);

// ==================== FUNÇÕES DO JOGADOR (move.c) ====================
void    player_init(t_player *player, int x, int y);
void    player_move(t_game *game, int dx, int dy);
void    player_reset(t_game *game);
bool    can_move(t_game *game, int x, int y);

// ==================== FUNÇÕES DE INIMIGO (enemy_funct.c) ====================
void    enemy_init(t_enemy *enemy, int x, int y);
void    enemy_update(t_game *game);
void    enemy_chase_player(t_enemy *enemy, t_position playerPos, t_map *map);
bool    check_collision_with_enemies(t_game *game, int x, int y);
void    enemies_reset(t_game *game);

// ==================== FUNÇÕES DE RENDERIZAÇÃO (render.c) ====================
void    render_game(t_game *game);
void    render_map(t_game *game);
void    render_entities(t_game *game);
void    render_ui(t_game *game);
void    render_menu(t_game *game);
void    render_game_over(t_game *game);
void    render_victory(t_game *game);

// ==================== FUNÇÕES DE ANIMAÇÃO (animation.c) ====================
void    animation_init(t_animation *anim, float speed);
void    animation_update(t_animation *anim);
void    animation_draw(t_animation *anim, int x, int y);
void    player_animation_update(t_player *player);
void    enemy_animation_update(t_enemy *enemy);

// ==================== FUNÇÕES DE IMAGENS (imgs.c) ====================
void    load_textures(t_game *game);
void    unload_textures(t_game *game);
Texture2D create_colored_texture(int width, int height, Color color);
void    load_player_textures(t_game *game);
void    load_enemy_textures(t_game *game);

// ==================== FUNÇÕES PRINCIPAIS (so_long.c) ====================
void    game_init(t_game *game, const char *mapFile);
void    game_update(t_game *game);
void    game_restart_level(t_game *game);
void    game_free(t_game *game);
void    handle_input(t_game *game);

// ==================== FUNÇÕES UTILITÁRIAS (utils.c) ====================
void    timer_start(t_timer *timer);
void    timer_stop(t_timer *timer);
void    timer_update(t_timer *timer);
void    timer_reset(t_timer *timer);
char    *ft_strdup(const char *s);
size_t  ft_strlen(const char *s);
void    error_exit(const char *message);
void    print_moves(int moves);

#endif // SO_LONG_H