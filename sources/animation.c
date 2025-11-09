#include "raylib.h"
#include "../includes/so_long.h"

int anime_enemy(t_game *game, int anim_state)
{
    int i;
    int x;
    int y;

    i = 0;
    while (game->map[i])
    {
        if (game->map[i] == 'R' || game->map[i] == 'r' ||
            game->map[i] == 'L' || game->map[i] == 'l')
        {
            find_x_y(*game, i, &x, &y);
            if (anim_state == 0 || anim_state == 6)
                put_image(*game, 'R', x * 96, y * 96);
            else if (anim_state == 1 || anim_state == 5)
                put_image(*game, 'T', x * 96, y * 96);
            else if (anim_state == 2 || anim_state == 4)
                put_image(*game, 'Y', x * 96, y * 96);
            else if (anim_state == 3)
                put_image(*game, 'U', x * 96, y * 96);
        }
        i++;
    }
    return 0;
}

int loop_animations(t_game *game)
{
    game->loop_state++;
    if (game->loop_state > 6000)
        game->loop_state = 0;

    if (game->loop_state % 1000 == 0)
        anime_enemy(game, game->loop_state / 1000);

    if (game->loop_state % 6000 == 0)
        change_enemys_pos(game);

    return 0;
}
