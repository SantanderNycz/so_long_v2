#include "../includes/so_long.h"

void game_init(t_game *game, const char *mapFile) {
    // Zerar estrutura
    memset(game, 0, sizeof(t_game));
    
    // Carregar mapa
    if (!map_load(&game->map, mapFile)) {
        error_exit("Failed to load map");
    }
    
    // Validar mapa
    if (!check_map_valid(&game->map)) {
        map_free(&game->map);
        error_exit("Invalid map");
    }
    
    // Verificar solvability
    if (!check_solvability(&game->map)) {
        map_free(&game->map);
        error_exit("Map is not solvable");
    }
    
    game->state = GAME_PLAYING;
    game->exitOpen = false;
    game->enemyCount = 0;
    game->collectibleCount = 0;
    
    // Alocar espaço para inimigos
    game->enemies = (t_enemy *)malloc(sizeof(t_enemy) * MAX_ENEMIES);
    if (!game->enemies) {
        map_free(&game->map);
        error_exit("Failed to allocate enemies");
    }
    
    // Alocar espaço para coletáveis
    game->collectibles = (t_collectible *)malloc(sizeof(t_collectible) * game->map.totalCollectibles);
    if (!game->collectibles) {
        free(game->enemies);
        map_free(&game->map);
        error_exit("Failed to allocate collectibles");
    }
    
    // Encontrar posições de jogador, inimigos e coletáveis
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            char tile = game->map.grid[y][x];
            
            if (tile == TILE_PLAYER) {
                player_init(&game->player, x, y);
                game->map.grid[y][x] = TILE_EMPTY;
            }
            else if (tile == TILE_ENEMY && game->enemyCount < MAX_ENEMIES) {
                enemy_init(&game->enemies[game->enemyCount], x, y);
                game->enemyCount++;
                game->map.grid[y][x] = TILE_EMPTY;
            }
            else if (tile == TILE_COLLECTIBLE) {
                game->collectibles[game->collectibleCount].pos.x = x;
                game->collectibles[game->collectibleCount].pos.y = y;
                game->collectibles[game->collectibleCount].collected = false;
                game->collectibles[game->collectibleCount].currentFrame = 0;
                game->collectibles[game->collectibleCount].frameTimer = 0.0f;
                game->collectibles[game->collectibleCount].animating = false;
                game->collectibles[game->collectibleCount].animationTime = 0.0f;
                game->collectibleCount++;
                game->map.grid[y][x] = TILE_EMPTY;
            }
        }
    }
    
    // Iniciar timer
    timer_start(&game->timer);
    
    printf("\n=== Game Initialized ===\n");
    printf("Map: %dx%d\n", game->map.width, game->map.height);
    printf("Collectibles: %d\n", game->collectibleCount);
    printf("Enemies: %d\n", game->enemyCount);
    printf("=======================\n\n");
}

void game_update(t_game *game) {
    if (game->state != GAME_PLAYING) {
        return;
    }
    
    float deltaTime = GetFrameTime();
    
    // Atualizar timer
    timer_update(&game->timer);
    
    // Atualizar animações do jogador
    player_animation_update(&game->player);
    
    // Atualizar animações dos inimigos (troca a cada 1 segundo)
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].active) {
            game->enemies[i].animation.frameTimer += deltaTime;
            if (game->enemies[i].animation.frameTimer >= game->enemies[i].animation.frameSpeed) {
                game->enemies[i].animation.frameTimer = 0.0f;
                game->enemies[i].animation.currentFrame = (game->enemies[i].animation.currentFrame + 1) % ENEMY_ANIMATION_FRAMES;
            }
        }
    }
    
    // Atualizar animações dos coletáveis
    for (int i = 0; i < game->collectibleCount; i++) {
        if (game->collectibles[i].animating) {
            game->collectibles[i].animationTime += deltaTime;
            
            // Frame 1 (animação) por 2 segundos
            if (game->collectibles[i].animationTime < 2.0f) {
                game->collectibles[i].currentFrame = 1;
            } else {
                // Frame 2 (estado final) após 2 segundos
                game->collectibles[i].currentFrame = 2;
                game->collectibles[i].animating = false;
            }
        }
    }
    
    // Atualizar inimigos
    enemy_update(game);
    
    // Verificar se coletou todos os itens
    if (game->player.collectibles >= game->map.totalCollectibles) {
        game->exitOpen = true;
    }
    
    // Verificar colisão com inimigos
    if (check_collision_with_enemies(game, game->player.pos.x, game->player.pos.y)) {
        game->state = GAME_OVER;
        timer_stop(&game->timer);
    }
}

void game_restart_level(t_game *game) {
    // Resetar jogador
    player_reset(game);
    
    // Resetar inimigos
    enemies_reset(game);
    
    // Recarregar mapa
    char *filename = ft_strdup(game->map.filename);
    map_free(&game->map);
    
    if (!map_load(&game->map, filename)) {
        free(filename);
        error_exit("Failed to reload map");
    }
    free(filename);
    
    // Reinicializar elementos
    game->enemyCount = 0;
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            char tile = game->map.grid[y][x];
            
            if (tile == TILE_PLAYER) {
                player_init(&game->player, x, y);
                game->map.grid[y][x] = TILE_EMPTY;
            }
            else if (tile == TILE_ENEMY && game->enemyCount < MAX_ENEMIES) {
                enemy_init(&game->enemies[game->enemyCount], x, y);
                game->enemyCount++;
                game->map.grid[y][x] = TILE_EMPTY;
            }
        }
    }
    
    game->state = GAME_PLAYING;
    game->exitOpen = false;
    timer_reset(&game->timer);
    timer_start(&game->timer);
}

void game_free(t_game *game) {
    map_free(&game->map);
    
    if (game->enemies) {
        free(game->enemies);
        game->enemies = NULL;
    }
    
    unload_textures(game);
}

void handle_input(t_game *game) {
    // Reiniciar
    if (IsKeyPressed(KEY_R)) {
        game_restart_level(game);
        return;
    }
    
    if (game->state == GAME_MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            game->state = GAME_PLAYING;
            timer_start(&game->timer);
        }
        return;
    }
    
    if (game->state != GAME_PLAYING) {
        return;
    }
    
    // Movimento do jogador
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        player_move(game, 0, -1);
    }
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        player_move(game, 0, 1);
    }
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        player_move(game, -1, 0);
    }
    else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        player_move(game, 1, 0);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <map_file.ber>\n", argv[0]);
        return 1;
    }

    t_game game;
    
    // Inicializar o jogo
    game_init(&game, argv[1]);

    // Inicializar a janela DEPOIS de carregar o mapa
    int windowWidth = game.map.width * TILE_SIZE;
    int windowHeight = game.map.height * TILE_SIZE + 50;
    
    InitWindow(windowWidth, windowHeight, "so_long");
    SetTargetFPS(60);

    // Carregar texturas DEPOIS de inicializar a janela
    load_textures(&game);

    printf("Window initialized: %dx%d\n", windowWidth, windowHeight);
    printf("Press WASD or Arrow Keys to move\n");
    printf("Press R to restart\n");
    printf("Press ESC to quit\n\n");

    // Loop principal
    while (!WindowShouldClose()) {
        // ===== ATUALIZAR =====
        handle_input(&game);
        game_update(&game);

        // ===== RENDERIZAR =====
        BeginDrawing();
        
            ClearBackground(BLACK);
            
            // Renderizar baseado no estado
            switch (game.state) {
                case GAME_MENU:
                    render_menu(&game);
                    break;
                    
                case GAME_PLAYING:
                    render_game(&game);
                    render_ui(&game);
                    break;
                    
                case GAME_WIN:
                    render_victory(&game);
                    break;
                    
                case GAME_OVER:
                    render_game_over(&game);
                    break;
            }
        
        EndDrawing();
        // ===== FIM DA RENDERIZAÇÃO =====
    }

    // Limpeza
    printf("\nCleaning up...\n");
    game_free(&game);
    CloseWindow();

    return 0;
}