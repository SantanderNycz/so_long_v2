#include "../includes/so_long.h"

void player_init(t_player *player, int x, int y) {
    if (!player)
        return;
    
    player->pos.x = x;
    player->pos.y = y;
    player->startPos.x = x;
    player->startPos.y = y;
    player->collectibles = 0;
    player->moves = 0;
    player->direction = 0; // down
    
    animation_init(&player->animation, ANIMATION_SPEED);
}

bool can_move(t_game *game, int x, int y) {
    if (!game)
        return false;
    
    // Verificar colisão com parede
    char tile = map_get_tile(&game->map, x, y);
    if (tile == TILE_WALL)
        return false;
    
    // Verificar se pode sair
    if (tile == TILE_EXIT && !game->exitOpen)
        return false;
    
    return true;
}

void player_move(t_game *game, int dx, int dy) {
    if (!game)
        return;
    
    int newX = game->player.pos.x + dx;
    int newY = game->player.pos.y + dy;
    
    // Atualizar direção
    if (dx > 0)
        game->player.direction = 3; // right
    else if (dx < 0)
        game->player.direction = 2; // left
    else if (dy > 0)
        game->player.direction = 0; // down
    else if (dy < 0)
        game->player.direction = 1; // up
    
    // Verificar se pode mover
    if (!can_move(game, newX, newY))
        return;
    
    char tile = map_get_tile(&game->map, newX, newY);
    
    // Verificar se chegou na saída
    if (tile == TILE_EXIT && game->exitOpen) {
        game->state = GAME_WIN;
        timer_stop(&game->timer);
        printf("\n=== VICTORY ===\n");
        printf("Time: %.2f seconds\n", game->timer.elapsedTime);
        printf("Moves: %d\n", game->player.moves + 1);
        printf("===============\n\n");
        return;
    }
    
    // Verificar se coletou item (agora verifica no array de coletáveis)
    for (int i = 0; i < game->collectibleCount; i++) {
        if (!game->collectibles[i].collected &&
            game->collectibles[i].pos.x == newX &&
            game->collectibles[i].pos.y == newY) {
            
            game->collectibles[i].collected = true;
            game->collectibles[i].animating = true;
            game->collectibles[i].animationTime = 0.0f;
            game->collectibles[i].currentFrame = 1; // Começa na animação
            game->player.collectibles++;
            
            printf("Collected! (%d/%d)\n", game->player.collectibles, game->map.totalCollectibles);
            break;
        }
    }
    
    // Mover jogador
    game->player.pos.x = newX;
    game->player.pos.y = newY;
    game->player.moves++;
    
    print_moves(game->player.moves);
}

void player_reset(t_game *game) {
    if (!game)
        return;
    
    game->player.pos = game->player.startPos;
    game->player.collectibles = 0;
    game->player.moves = 0;
    game->player.direction = 0;
    game->exitOpen = false;
}