#include "../includes/raylib.h"
#include "../includes/so_long.h"

int close_program(t_game *game)
{
    if (game->map)
        free(game->map);

    close_img(game);
    close_img_wall(game);

    CloseWindow(); // Fecha a janela Raylib
    exit(0);
    return 0;
}

void handle_input(t_game *game)
{
    if (IsKeyPressed(KEY_ESCAPE))
        close_program(game);
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
        move_check(game, 't');
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT_SHIFT))
        move_check(game, 'b');
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        move_check(game, 'l');
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        move_check(game, 'r');
}

int main(int argc, char **argv)
{
    t_game *game;

    memset(&game, 0, sizeof(t_game));
    game.game_state = 0;

    if (argc != 2)
        return (printf("Uso: %s <mapa.ber>\n", argv[0]), 1);

    check_map(&game, argv[1]);
    game.collect = nb_occurrence(game.map, 'C');
    game.player_pos = find_index(game.map, 'P');
    game.game_state = 3;

    // Inicializa janela Raylib
    InitWindow(game.map_w * 96, game.map_h * 96, "So_long Raylib Edition");
    SetTargetFPS(60);

    open_imgs(NULL, &game); // se a função não usar mlx, só game
    add_enemy(&game);
    game.game_state = 4;

    // Loop principal
    while (!WindowShouldClose())
    {
        handle_input(&game);
        loop_animations(&game);

        BeginDrawing();
            ClearBackground(BLACK);
            fill_win(&game);
        EndDrawing();
    }

    close_program(&game);
    return 0;
}
