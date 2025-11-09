#include "../includes/so_long.h"

int put_image(t_game game, char c, int x, int y)
{
    Texture2D img = game.assets.bg_1;

    if (c == '1')
        img = get_wall(game, x, y);
    else if (c == '0')
        img = game.assets.bg_1;
    else if (c == 'C')
        img = game.assets.chest;
    else if (c == 'O')
        img = game.assets.chest_o;
    else if (c == 'P')
        img = game.assets.player;
    else if (c == 'E')
        img = game.assets.exit;
    else if (c == 'R')
        img = game.assets.enemy_0;
    else if (c == 'T')
        img = game.assets.enemy_1;
    else if (c == 'Y')
        img = game.assets.enemy_2;
    else if (c == 'U')
        img = game.assets.enemy_3;

    DrawTexture(img, x, y, WHITE);
    return 0;
}

Texture2D get_wall(t_game game, int x, int y)
{
    Texture2D img = game.assets.wall;

    if (y / 96 == 0)
        img = game.assets.wall_t;
    else if (y / 96 == game.map_h - 1)
        img = game.assets.wall_b;
    else if (x / 96 == 0)
        img = game.assets.wall_l;
    else if (x / 96 == game.map_w - 1)
        img = game.assets.wall_r;

    if (x / 96 == 0 && y / 96 == 0)
        img = game.assets.wall_tl;
    else if (x / 96 == game.map_w - 1 && y / 96 == 0)
        img = game.assets.wall_tr;
    else if (x / 96 == 0 && y / 96 == game.map_h - 1)
        img = game.assets.wall_bl;
    else if (x / 96 == game.map_w - 1 && y / 96 == game.map_h - 1)
        img = game.assets.wall_br;

    return img;
}

int fill_win(t_game game)
{
    size_t i;
    int x, y;

    i = 0;
    while (i < ft_strlen(game.map))
    {
        if (game.map[i] != '\n')
        {
            find_x_y(game, i, &x, &y);
            put_image(game, game.map[i], x * 96, y * 96);
        }
        i++;
    }
    return 0;
}
