#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"

// Constantes
#define TILE_SIZE 64
#define MAX_LEVELS 10
#define MAX_ENEMIES 20
#define PLAYER_SPEED 4
#define ENEMY_SPEED 2

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
typedef struct {
    int x;
    int y;
} Position;

// Estrutura do jogador
typedef struct {
    Position pos;
    Position startPos;
    int collectibles;
    int moves;
    Texture2D texture;
} Player;

// Estrutura do inimigo
typedef struct {
    Position pos;
    Position target;
    bool active;
    float moveTimer;
    Texture2D texture;
} Enemy;

// Estrutura do mapa
typedef struct {
    char **grid;
    int width;
    int height;
    int totalCollectibles;
    char *filename;
} Map;

// Estrutura do timer
typedef struct {
    double startTime;
    double elapsedTime;
    bool running;
} GameTimer;

// Estrutura principal do jogo
typedef struct {
    Map map;
    Player player;
    Enemy enemies[MAX_ENEMIES];
    int enemyCount;
    GameState state;
    GameTimer timer;
    int currentLevel;
    char *levelFiles[MAX_LEVELS];
    int totalLevels;
    Texture2D textures[6]; // wall, floor, collectible, exit, player, enemy
    bool exitOpen;
} Game;

// Funções de mapa
bool map_load(Map *map, const char *filename);
void map_free(Map *map);
bool map_validate(Map *map);
char map_get_tile(Map *map, int x, int y);
void map_set_tile(Map *map, int x, int y, char tile);

// Funções do jogador
void player_init(Player *player, int x, int y);
void player_move(Game *game, int dx, int dy);
void player_reset(Game *game);

// Funções de inimigo
void enemy_init(Enemy *enemy, int x, int y);
void enemy_update(Game *game);
void enemy_chase_player(Enemy *enemy, Position playerPos);
bool check_collision_with_enemies(Game *game, int x, int y);

// Funções de renderização
void render_game(Game *game);
void render_ui(Game *game);
void render_menu(Game *game);
void render_game_over(Game *game);
void render_victory(Game *game);

// Funções de entrada
void handle_input(Game *game);

// Funções do timer
void timer_start(GameTimer *timer);
void timer_stop(GameTimer *timer);
void timer_update(GameTimer *timer);
void timer_reset(GameTimer *timer);

// Funções do gerenciador de níveis
void level_manager_init(Game *game);
bool level_manager_load_next(Game *game);
void level_manager_reset(Game *game);

// Funções principais
void game_init(Game *game);
void game_load_textures(Game *game);
void game_free(Game *game);
void game_update(Game *game);
void game_restart_level(Game *game);

#endif // SO_LONG_H