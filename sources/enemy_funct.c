#include "raylib.h"
#include "../includes/so_long.h"

int enemy_can_be_place(int i, char *m)
{
    if (get_ind(i, m, 'l') != -1 && m[get_ind(i, m, 'l')] == '0' &&
        get_ind(i, m, 'b') != -1 && m[get_ind(i, m, 'b')] == '0')
    {
        if (m[i] == '0' && m[get_ind(get_ind(i, m, 'l'), m, 'b')] == '0')
        {
            if (m[get_ind(i, m, 't')] != 'R' &&
                m[get_ind(get_ind(i, m, 'l'), m, 't')] != 'R')
            {
                return 1;
            }
        }
    }
    return 0;
}

int add_enemy(t_game *game)
{
    int i;

    i = -1;
    while (game->map[++i])
        if ((rand() % 5) < 1 && enemy_can_be_place(i, game->map))
            game->map[i] = 'R';
    if (nb_occurrence(game->map, 'R') == 0)
        ft_printf_e(WARN_NO_ENEMY);
    return 0;
}

int kill_player(t_game *game, int enemy_pos, char *map_cpy)
{
    if (enemy_pos == game->player_pos)
        return (free(map_cpy), ft_printf(DEATH), close_program(game), 0);
    return 0;
}

char *move_enemy(t_game *game, int from, char state, char *map_cpy)
{
    int x;
    int y;

    find_x_y(*game, from, &x, &y);
    DrawRectangle(x * 96, y * 96, 96, 96, BLACK);
    map_cpy[from] = '0';
    if (state == 'R')
    {
        DrawRectangle(x * 96, y * 96 + 96, 96, 96, RED);
        kill_player(game, get_ind(from, game->map, 'b'), map_cpy);
        map_cpy[get_ind(from, game->map, 'b')] = 'r';
    }
    else if (state == 'r')
    {
        DrawRectangle(x * 96 - 96, y * 96, 96, 96, RED);
        kill_player(game, get_ind(from, game->map, 'l'), map_cpy);
        map_cpy[get_ind(from, game->map, 'l')] = 'l';
    }
    else if (state == 'l')
    {
        DrawRectangle(x * 96, y * 96 - 96, 96, 96, RED);
        kill_player(game, get_ind(from, game->map, 't'), map_cpy);
        map_cpy[get_ind(from, game->map, 't')] = 'L';
    }
    else if (state == 'L')
    {
        DrawRectangle(x * 96 + 96, y * 96, 96, 96, RED);
        kill_player(game, get_ind(from, game->map, 'r'), map_cpy);
        map_cpy[get_ind(from, game->map, 'r')] = 'R';
    }
    return map_cpy;
}

int change_enemys_pos(t_game *game)
{
    char *map_cpy;
    int i;

    i = -1;
    map_cpy = ft_strdup(game->map);
    if (!map_cpy)
        return (close_program(game), 1);
    while (game->map[++i])
        if (game->map[i] == 'R' || game->map[i] == 'r' ||
            game->map[i] == 'L' || game->map[i] == 'l')
            if ((rand() % 5) < 3)
                map_cpy = move_enemy(game, i, game->map[i], map_cpy);
    free(game->map);
    game->map = map_cpy;
    return 0;
}

