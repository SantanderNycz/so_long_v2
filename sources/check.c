#include "../includes/so_long.h"

bool check_rectangular(t_map *map) {
    if (!map || !map->grid)
        return false;
    
    for (int y = 0; y < map->height; y++) {
        if ((int)ft_strlen(map->grid[y]) != map->width) {
            printf("Error: Map is not rectangular at line %d\n", y + 1);
            return false;
        }
    }
    return true;
}

bool check_walls(t_map *map) {
    if (!map || !map->grid)
        return false;
    
    // Verificar primeira e última linha
    for (int x = 0; x < map->width; x++) {
        if (map->grid[0][x] != TILE_WALL) {
            printf("Error: Top wall incomplete at column %d\n", x + 1);
            return false;
        }
        if (map->grid[map->height - 1][x] != TILE_WALL) {
            printf("Error: Bottom wall incomplete at column %d\n", x + 1);
            return false;
        }
    }
    
    // Verificar primeira e última coluna
    for (int y = 0; y < map->height; y++) {
        if (map->grid[y][0] != TILE_WALL) {
            printf("Error: Left wall incomplete at row %d\n", y + 1);
            return false;
        }
        if (map->grid[y][map->width - 1] != TILE_WALL) {
            printf("Error: Right wall incomplete at row %d\n", y + 1);
            return false;
        }
    }
    
    return true;
}

bool check_characters(t_map *map) {
    if (!map || !map->grid)
        return false;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char c = map->grid[y][x];
            if (c != TILE_EMPTY && c != TILE_WALL && c != TILE_PLAYER &&
                c != TILE_COLLECTIBLE && c != TILE_EXIT && c != TILE_ENEMY) {
                printf("Error: Invalid character '%c' at position (%d, %d)\n", c, x + 1, y + 1);
                return false;
            }
        }
    }
    return true;
}

bool check_elements(t_map *map) {
    if (!map || !map->grid)
        return false;
    
    int playerCount = 0;
    int exitCount = 0;
    int collectibleCount = 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char tile = map->grid[y][x];
            
            if (tile == TILE_PLAYER)
                playerCount++;
            else if (tile == TILE_EXIT)
                exitCount++;
            else if (tile == TILE_COLLECTIBLE)
                collectibleCount++;
        }
    }
    
    if (playerCount != 1) {
        printf("Error: Map must have exactly 1 player (found %d)\n", playerCount);
        return false;
    }
    
    if (exitCount != 1) {
        printf("Error: Map must have exactly 1 exit (found %d)\n", exitCount);
        return false;
    }
    
    if (collectibleCount < 1) {
        printf("Error: Map must have at least 1 collectible (found %d)\n", collectibleCount);
        return false;
    }
    
    map->totalCollectibles = collectibleCount;
    return true;
}

bool check_map_valid(t_map *map) {
    if (!map) {
        printf("Error: Map is NULL\n");
        return false;
    }
    
    if (!check_rectangular(map))
        return false;
    
    if (!check_walls(map))
        return false;
    
    if (!check_characters(map))
        return false;
    
    if (!check_elements(map))
        return false;
    
    map->isValid = true;
    return true;
}