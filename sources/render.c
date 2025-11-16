#include "../includes/so_long.h"

void render_map(t_game *game) {
    if (!game || !game->map.grid)
        return;
    
    // Renderizar cada tile do mapa
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            int screenX = x * TILE_SIZE;
            int screenY = y * TILE_SIZE;
            
            char tile = map_get_tile(&game->map, x, y);
            
            // Sempre desenhar o chão primeiro
            DrawTexture(game->textures.floor, screenX, screenY, WHITE);
            
            // Desenhar tile específico por cima
            switch (tile) {
                case TILE_WALL:
                    DrawTexture(game->textures.wall, screenX, screenY, WHITE);
                    break;
                    
                case TILE_EXIT:
                    if (game->exitOpen) {
                        DrawTexture(game->textures.exit_open, screenX + 5, screenY + 5, WHITE);
                    } else {
                        DrawTexture(game->textures.exit_closed, screenX + 5, screenY + 5, WHITE);
                    }
                    break;
            }
        }
    }
    
    // Desenhar coletáveis (sempre visíveis, mas mudam de frame quando coletados)
    for (int i = 0; i < game->collectibleCount; i++) {
        int screenX = game->collectibles[i].pos.x * TILE_SIZE + 10;
        int screenY = game->collectibles[i].pos.y * TILE_SIZE + 10;
        int frame = game->collectibles[i].currentFrame;
        
        DrawTexture(game->textures.collectible[frame], screenX, screenY, WHITE);
    }
}


void render_entities(t_game *game)
{
    // Desenhar inimigos
    for (int i = 0; i < game->enemyCount; i++)
    {
        DrawTexture(game->textures.enemy[game->enemies[i].animation.currentFrame],
                    game->enemies[i].pos.x * TILE_SIZE,
                    game->enemies[i].pos.y * TILE_SIZE, WHITE);
    }

    // Desenhar coletáveis
    for (int i = 0; i < game->collectibleCount; i++)
    {
        if (!game->collectibles[i].collected)
        {
            int frame = game->collectibles[i].currentFrame;
            DrawTexture(game->textures.collectible[frame],
                        game->collectibles[i].pos.x * TILE_SIZE + 10,
                        game->collectibles[i].pos.y * TILE_SIZE + 10, WHITE);
        }
    }

    // Desenhar jogador
    DrawTexture(game->textures.player[game->player.animation.currentFrame],
                game->player.pos.x * TILE_SIZE,
                game->player.pos.y * TILE_SIZE, WHITE);
}

void render_game(t_game *game) {
    if (!game)
        return;
    
    render_map(game);
    render_entities(game);
}

void render_ui(t_game *game) {
    if (!game)
        return;
    
    int uiY = game->map.height * TILE_SIZE + 5;
    
    // Fundo da UI
    DrawRectangle(0, game->map.height * TILE_SIZE, 
                 game->map.width * TILE_SIZE, 50, DARKGRAY);
    
    // Informações do jogo
    char info[256];
    snprintf(info, sizeof(info), "Moves: %d | Items: %d/%d | Time: %.1f s", 
             game->player.moves, 
             game->player.collectibles, 
             game->map.totalCollectibles,
             game->timer.elapsedTime);
    
    DrawText(info, 10, uiY, 18, WHITE);
    
    // Instruções
    if (game->player.collectibles < game->map.totalCollectibles) {
        DrawText("Collect all items!", 10, uiY + 25, 15, YELLOW);
    } else {
        DrawText("Exit is open! Go!", 10, uiY + 25, 15, GREEN);
    }
}

void render_menu(t_game *game) {
    if (!game)
        return;
    
    int centerX = (game->map.width * TILE_SIZE) / 2;
    int centerY = (game->map.height * TILE_SIZE) / 2;
    
    DrawText("SO_LONG", centerX - 100, centerY - 100, 40, WHITE);
    DrawText("Press ENTER to start", centerX - 120, centerY, 20, LIGHTGRAY);
    DrawText("Use WASD or Arrow Keys to move", centerX - 150, centerY + 40, 16, GRAY);
    DrawText("Press R to restart level", centerX - 120, centerY + 70, 16, GRAY);
    DrawText("Press ESC to quit", centerX - 90, centerY + 100, 16, GRAY);
}

void render_game_over(t_game *game) {
    if (!game)
        return;
    
    render_game(game);
    render_ui(game);
    
    int centerX = (game->map.width * TILE_SIZE) / 2;
    int centerY = (game->map.height * TILE_SIZE) / 2;
    
    DrawRectangle(0, 0, game->map.width * TILE_SIZE, 
                 game->map.height * TILE_SIZE, Fade(BLACK, 0.7f));
    
    DrawText("GAME OVER!", centerX - 120, centerY - 50, 40, RED);
    DrawText("You were caught by an enemy!", centerX - 140, centerY + 20, 20, WHITE);
    
    char stats[128];
    snprintf(stats, sizeof(stats), "Time: %.1f s | Moves: %d", 
             game->timer.elapsedTime, game->player.moves);
    DrawText(stats, centerX - 120, centerY + 60, 18, LIGHTGRAY);
    
    DrawText("Press R to restart", centerX - 90, centerY + 100, 20, YELLOW);
    DrawText("Press ESC to quit", centerX - 85, centerY + 130, 20, GRAY);
}

void render_victory(t_game *game) {
    if (!game)
        return;
    
    render_game(game);
    render_ui(game);
    
    int centerX = (game->map.width * TILE_SIZE) / 2;
    int centerY = (game->map.height * TILE_SIZE) / 2;
    
    DrawRectangle(0, 0, game->map.width * TILE_SIZE, 
                 game->map.height * TILE_SIZE, Fade(BLACK, 0.7f));
    
    DrawText("VICTORY!", centerX - 90, centerY - 50, 40, GREEN);
    
    char stats[128];
    snprintf(stats, sizeof(stats), "Time: %.1f s | Moves: %d", 
             game->timer.elapsedTime, game->player.moves);
    DrawText(stats, centerX - 100, centerY + 20, 20, WHITE);
    
    char collectibles[128];
    snprintf(collectibles, sizeof(collectibles), "Collectibles: %d/%d", 
             game->player.collectibles, game->map.totalCollectibles);
    DrawText(collectibles, centerX - 100, centerY + 60, 18, GOLD);
    
    DrawText("Press R to restart", centerX - 90, centerY + 100, 20, YELLOW);
    DrawText("Press ESC to quit", centerX - 85, centerY + 130, 20, GRAY);
}