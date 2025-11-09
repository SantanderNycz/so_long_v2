#include "../includes/so_long.h"

int move_check(t_game *game, char direction)
{
    int temp_i = get_ind(game->player_pos, game->map, direction);
    if (temp_i == -1)
        return -1;
    if (game->map[temp_i] == '1')
        return 0;
    if (game->map[temp_i] == 'R' || game->map[temp_i] == 'r' || 
        game->map[temp_i] == 'L' || game->map[temp_i] == 'l')
        return ft_printf(DEATH), close_program(game), 0;
    if (game->map[temp_i] == 'C')
    {
        game->collect--;
        move_player(game, game->player_pos, direction);
    }
    if (game->map[temp_i] == '0' || game->map[temp_i] == 'P' || 
        game->map[temp_i] == 'E' || game->map[temp_i] == 'O')
        move_player(game, game->player_pos, direction);
    if (game->map[temp_i] == 'E' && game->collect == 0)
        return ft_printf(WIN), close_program(game), 0;
    game->player_pos = temp_i;
    game->move++;
    return 0;
}

int update_displayed_move(t_game *game)
{
    char *temp;
    DrawText("Número de movimentos:", 10, 10, 20, WHITE);
    temp = ft_itoa(game->move + 1);
    DrawText(temp, 200, 10, 20, WHITE);
    free(temp);
    return 0;
}

int move_player_set_datas(t_game *game, int from_pos, int x, int y)
{
    if (game->map[from_pos] == 'C' || game->map[from_pos] == 'O')
    {
        DrawTexture(game->assets.chest_o, x, y, WHITE);
        game->map[from_pos] = 'O';
    }
    if (game->map[from_pos] == 'E')
        DrawTexture(game->assets.exit, x, y, WHITE);
    return 0;
}

int update_x_y(char direction, int i, int *x, int *y)
{
    int step = 96 / 8;
    if (i % 1000 != 0)
        return 0;
    if (direction == 't')
        *y -= step;
    else if (direction == 'b')
        *y += step;
    else if (direction == 'r')
        *x += step;
    else if (direction == 'l')
        *x -= step;
    return 0;
}

int move_player(t_game *game, int fpos, char direction)
{
    int i, x, y, from_x, from_y;
    find_x_y(*game, fpos, &x, &y);
    x *= 96; from_x = x;
    y *= 96; from_y = y;
    move_player_set_datas(game, fpos, x, y);
    for (i = 0; i < 8000; i++)
    {
        if (i % 1000 == 0)
        {
            if (game->map[fpos] == 'C' || game->map[fpos] == 'O')
                DrawTexture(game->assets.chest_o, from_x, from_y, WHITE);
            else if (game->map[fpos] == 'E')
                DrawTexture(game->assets.exit, from_x, from_y, WHITE);
            else
                DrawTexture(game->assets.bg_1, from_x, from_y, WHITE);
        }
        update_x_y(direction, i, &x, &y);
        DrawTexture(game->assets.player, x, y, WHITE);
    }
    return update_displayed_move(game), 0;
}
