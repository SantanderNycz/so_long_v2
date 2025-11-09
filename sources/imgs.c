#include "raylib.h"
#include "../includes/so_long.h"

int check_img_opened(t_game *game)
{
    t_assets *a = &game->assets;
    if (!a->bg_1 || !a->chest_o || !a->chest || !a->wall || !a->exit ||
        !a->player || !a->enemy_0 || !a->enemy_1 || !a->enemy_2 ||
        !a->enemy_3 || !a->wall_bl || !a->wall_br || !a->wall_tl ||
        !a->wall_tr || !a->wall_t || !a->wall_b || !a->wall_l || !a->wall_r)
        return close_program(game);
    return 0;
}

int open_imgs(t_game *game)
{
    t_assets *a = &game->assets;

    a->bg_1     = LoadTexture("./assets/bg.png");
    a->chest_o  = LoadTexture("./assets/chest_o.png");
    a->chest    = LoadTexture("./assets/chest.png");
    a->wall     = LoadTexture("./assets/wall.png");
    a->exit     = LoadTexture("./assets/exit.png");
    a->player   = LoadTexture("./assets/player.png");
    a->enemy_0  = LoadTexture("./assets/enemy_0.png");
    a->enemy_1  = LoadTexture("./assets/enemy_1.png");
    a->enemy_2  = LoadTexture("./assets/enemy_2.png");
    a->enemy_3  = LoadTexture("./assets/enemy_3.png");
    a->wall_bl  = LoadTexture("./assets/wall_bl.png");
    a->wall_br  = LoadTexture("./assets/wall_br.png");
    a->wall_tl  = LoadTexture("./assets/wall_tl.png");
    a->wall_tr  = LoadTexture("./assets/wall_tr.png");
    a->wall_t   = LoadTexture("./assets/wall_t.png");
    a->wall_b   = LoadTexture("./assets/wall_b.png");
    a->wall_l   = LoadTexture("./assets/wall_l.png");
    a->wall_r   = LoadTexture("./assets/wall_r.png");

    return check_img_opened(game);
}

int close_img(t_game *g)
{
    if (g->assets.bg_1.id != 0)       UnloadTexture(g->assets.bg_1);
    if (g->assets.chest_o.id != 0)    UnloadTexture(g->assets.chest_o);
    if (g->assets.chest.id != 0)      UnloadTexture(g->assets.chest);
    if (g->assets.wall.id != 0)       UnloadTexture(g->assets.wall);
    if (g->assets.exit.id != 0)       UnloadTexture(g->assets.exit);
    if (g->assets.player.id != 0)     UnloadTexture(g->assets.player);
    if (g->assets.enemy_0.id != 0)    UnloadTexture(g->assets.enemy_0);
    if (g->assets.enemy_1.id != 0)    UnloadTexture(g->assets.enemy_1);
    if (g->assets.enemy_2.id != 0)    UnloadTexture(g->assets.enemy_2);
    if (g->assets.enemy_3.id != 0)    UnloadTexture(g->assets.enemy_3);
    return 0;
}

int close_img_wall(t_game *g)
{
    if (g->assets.wall_bl.id != 0)    UnloadTexture(g->assets.wall_bl);
    if (g->assets.wall_br.id != 0)    UnloadTexture(g->assets.wall_br);
    if (g->assets.wall_tl.id != 0)    UnloadTexture(g->assets.wall_tl);
    if (g->assets.wall_tr.id != 0)    UnloadTexture(g->assets.wall_tr);
    if (g->assets.wall_t.id != 0)     UnloadTexture(g->assets.wall_t);
    if (g->assets.wall_b.id != 0)     UnloadTexture(g->assets.wall_b);
    if (g->assets.wall_l.id != 0)     UnloadTexture(g->assets.wall_l);
    if (g->assets.wall_r.id != 0)     UnloadTexture(g->assets.wall_r);
    return 0;
}
