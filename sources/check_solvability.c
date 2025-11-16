#include "../includes/so_long.h"

void free_visited(bool **visited, int height) {
    if (!visited)
        return;
    
    for (int i = 0; i < height; i++) {
        if (visited[i])
            free(visited[i]);
    }
    free(visited);
}

bool flood_fill_check(t_map *map, int x, int y, bool **visited, int *collectibles, bool *foundExit) {
    // Verificar limites
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return true;
    
    // Se já visitou ou é parede, retornar
    if (visited[y][x] || map->grid[y][x] == TILE_WALL)
        return true;
    
    // Marcar como visitado
    visited[y][x] = true;
    
    char tile = map->grid[y][x];
    
    // Contar coletável
    if (tile == TILE_COLLECTIBLE)
        (*collectibles)++;
    
    // Encontrou a saída
    if (tile == TILE_EXIT)
        *foundExit = true;
    
    // Recursão nas 4 direções (cima, baixo, esquerda, direita)
    flood_fill_check(map, x + 1, y, visited, collectibles, foundExit);
    flood_fill_check(map, x - 1, y, visited, collectibles, foundExit);
    flood_fill_check(map, x, y + 1, visited, collectibles, foundExit);
    flood_fill_check(map, x, y - 1, visited, collectibles, foundExit);
    
    return true;
}

bool check_solvability(t_map *map) {
    if (!map || !map->grid)
        return false;
    
    // Encontrar posição do jogador
    int playerX = -1;
    int playerY = -1;
    
    for (int y = 0; y < map->height && playerY == -1; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == TILE_PLAYER) {
                playerX = x;
                playerY = y;
                break;
            }
        }
    }
    
    if (playerX == -1 || playerY == -1) {
        printf("Error: Player not found in map\n");
        return false;
    }
    
    // Criar matriz de visitados
    bool **visited = (bool **)malloc(sizeof(bool *) * map->height);
    if (!visited) {
        printf("Error: Memory allocation failed for visited matrix\n");
        return false;
    }
    
    for (int i = 0; i < map->height; i++) {
        visited[i] = (bool *)calloc(map->width, sizeof(bool));
        if (!visited[i]) {
            free_visited(visited, i);
            printf("Error: Memory allocation failed for visited row %d\n", i);
            return false;
        }
    }
    
    // Fazer flood fill a partir da posição do jogador
    int collectiblesFound = 0;
    bool foundExit = false;
    
    flood_fill_check(map, playerX, playerY, visited, &collectiblesFound, &foundExit);
    
    // Verificar se encontrou todos os coletáveis e a saída
    bool solvable = (collectiblesFound == map->totalCollectibles && foundExit);
    
    if (!solvable) {
        printf("\n=== MAP SOLVABILITY CHECK ===\n");
        if (collectiblesFound != map->totalCollectibles) {
            printf("Error: Not all collectibles are reachable!\n");
            printf("       Found: %d/%d collectibles\n", 
                   collectiblesFound, map->totalCollectibles);
        }
        if (!foundExit) {
            printf("Error: Exit is not reachable!\n");
        }
        printf("============================\n\n");
    } else {
        printf("Map validation: OK (all collectibles and exit are reachable)\n");
    }
    
    free_visited(visited, map->height);
    
    map->isSolvable = solvable;
    return solvable;
}