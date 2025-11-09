#include "../includes/so_long.h"

int nb_occurrence(char *str, char c)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

int line_len(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\n')
            return i;
        i++;
    }
    return i;
}

int get_ind(int pos, char *map, char directions)
{
    int line_l = line_len(map) + 1;

    if (pos > 0 && map[pos] == '\n')
        return -1;

    if (directions == 't' && pos >= line_l)
        return pos - line_l;
    if (directions == 'b' && pos + line_l < (int)ft_strlen(map))
        return pos + line_l;
    if (directions == 'l' && pos - 1 >= 0 && map[pos - 1] != '\n')
        return pos - 1;
    if (directions == 'r' && map[pos + 1] && map[pos + 1] != '\n')
        return pos + 1;

    return -1;
}

int find_index(char *map, char to_find)
{
    int i = 0;

    while (map[i] && map[i] != to_find)
        i++;
    if (map[i] == to_find)
        return i;
    return -1;
}

int find_x_y(t_game game, int pos, int *x, int *y)
{
    int i = 0;
    *x = 0;
    *y = 0;

    while (i < pos && game.map[i])
    {
        if (game.map[i] == '\n')
        {
            (*y)++;
            *x = 0;
        }
        else
            (*x)++;
        i++;
    }
    return 0;
}

// Função para tratar teclas pressionadas
void key_press(t_game *game)
{
    if (IsKeyPressed(ESC_KEY))
        close_program(game);
    if (IsKeyPressed(UP_KEY) || IsKeyPressed(KEY_UP) || IsKeyPressed(SPACE_KEY))
        move_check(game, 't');
    if (IsKeyPressed(DOWN_KEY) || IsKeyPressed(KEY_DOWN))
        move_check(game, 'b');
    if (IsKeyPressed(LEFT_KEY) || IsKeyPressed(KEY_LEFT))
        move_check(game, 'l');
    if (IsKeyPressed(RIGHT_KEY) || IsKeyPressed(KEY_RIGHT))
        move_check(game, 'r');
}

// Atualiza o contador de movimentos na tela
void update_displayed_move(t_game *game)
{
    char *temp = ft_itoa(game->move + 1);
    // Desenha um retângulo de fundo para "limpar" o número anterior
    DrawRectangle(10, 10, 200, 20, BLACK);
    DrawText("Número de movimentos:", 10, 10, 10, WHITE_COLOR);
    DrawText(temp, 150, 10, 10, WHITE_COLOR);
    free(temp);
}