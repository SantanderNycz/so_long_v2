#include "../includes/so_long.h"

void enemy_init(t_enemy *enemy, int x, int y) {
    if (!enemy)
        return;
    
    enemy->pos.x = x;
    enemy->pos.y = y;
    enemy->startPos.x = x;
    enemy->startPos.y = y;
    enemy->target.x = x;
    enemy->target.y = y;
    enemy->active = true;
    enemy->moveTimer = 0.0f;
    enemy->direction = 0;
    
    animation_init(&enemy->animation, ANIMATION_SPEED);
}

void enemy_chase_player(t_enemy *enemy, t_position playerPos, t_map *map) {
    if (!enemy || !map)
        return;
    
    int dx = playerPos.x - enemy->pos.x;
    int dy = playerPos.y - enemy->pos.y;
    
    // Movimento simples em direção ao jogador
    if (abs(dx) > abs(dy)) {
        enemy->target.x = enemy->pos.x + (dx > 0 ? 1 : -1);
        enemy->target.y = enemy->pos.y;
        enemy->direction = (dx > 0) ? 3 : 2; // right : left
    } else {
        enemy->target.x = enemy->pos.x;
        enemy->target.y = enemy->pos.y + (dy > 0 ? 1 : -1);
        enemy->direction = (dy > 0) ? 0 : 1; // down : up
    }
}

void enemy_update(t_game *game) {
    if (!game)
        return;
    
    float deltaTime = GetFrameTime();
    
    for (int i = 0; i < game->enemyCount; i++) {
        t_enemy *enemy = &game->enemies[i];
        
        if (!enemy->active)
            continue;
        
        // Atualizar animação
        enemy_animation_update(enemy);
        
        enemy->moveTimer += deltaTime;
        
        // Mover inimigo a cada 0.5 segundos
        if (enemy->moveTimer >= 0.5f) {
            enemy->moveTimer = 0.0f;
            
            // Calcular direção para o jogador
            enemy_chase_player(enemy, game->player.pos, &game->map);
            
            // Verificar se o movimento é válido
            char tile = map_get_tile(&game->map, enemy->target.x, enemy->target.y);
            
            if (tile != TILE_WALL && tile != TILE_EXIT) {
                // Verificar colisão com outros inimigos
                bool blocked = false;
                for (int j = 0; j < game->enemyCount; j++) {
                    if (i != j && 
                        game->enemies[j].pos.x == enemy->target.x && 
                        game->enemies[j].pos.y == enemy->target.y) {
                        blocked = true;
                        break;
                    }
                }
                
                if (!blocked) {
                    enemy->pos = enemy->target;
                }
            }
        }
    }
}

bool check_collision_with_enemies(t_game *game, int x, int y) {
    if (!game)
        return false;
    
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].active && 
            game->enemies[i].pos.x == x && 
            game->enemies[i].pos.y == y) {
            printf("\n=== GAME OVER ===\n");
            printf("You were caught by an enemy!\n");
            printf("Time: %.2f seconds\n", game->timer.elapsedTime);
            printf("Moves: %d\n", game->player.moves);
            printf("=================\n\n");
            return true;
        }
    }
    return false;
}

void enemies_reset(t_game *game) {
    if (!game || !game->enemies)
        return;
    
    for (int i = 0; i < game->enemyCount; i++) {
        game->enemies[i].pos = game->enemies[i].startPos;
        game->enemies[i].target = game->enemies[i].startPos;
        game->enemies[i].active = true;
        game->enemies[i].moveTimer = 0.0f;
        game->enemies[i].direction = 0;
    }
}