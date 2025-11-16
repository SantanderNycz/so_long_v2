#include "../includes/so_long.h"

static int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file)
        return 0;
    
    int count = 0;
    char line[1024];
    
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    
    fclose(file);
    return count;
}

bool map_load(t_map *map, const char *filename) {
    if (!map || !filename) {
        printf("Error: Invalid parameters\n");
        return false;
    }
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return false;
    }

    map->height = count_lines(filename);
    if (map->height == 0) {
        fclose(file);
        printf("Error: Empty map file\n");
        return false;
    }

    map->grid = (char **)malloc(sizeof(char *) * map->height);
    if (!map->grid) {
        fclose(file);
        printf("Error: Memory allocation failed\n");
        return false;
    }

    char line[1024];
    int row = 0;
    
    rewind(file);
    
    while (fgets(line, sizeof(line), file) && row < map->height) {
        // Remover newline
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
            len--;
        }
        
        if (row == 0) {
            map->width = len;
        }
        
        map->grid[row] = (char *)malloc(len + 1);
        if (!map->grid[row]) {
            fclose(file);
            map_free(map);
            printf("Error: Memory allocation failed for row %d\n", row);
            return false;
        }
        
        for (size_t i = 0; i <= len; i++) {
            map->grid[row][i] = line[i];
        }
        row++;
    }
    
    fclose(file);
    
    map->filename = ft_strdup(filename);
    if (!map->filename) {
        map_free(map);
        return false;
    }
    
    map->totalCollectibles = map_count_collectibles(map);
    map->isValid = false;
    map->isSolvable = false;
    
    return true;
}

void map_free(t_map *map) {
    if (!map)
        return;
    
    if (map->grid) {
        for (int i = 0; i < map->height; i++) {
            if (map->grid[i]) {
                free(map->grid[i]);
                map->grid[i] = NULL;
            }
        }
        free(map->grid);
        map->grid = NULL;
    }
    
    if (map->filename) {
        free(map->filename);
        map->filename = NULL;
    }
    
    map->width = 0;
    map->height = 0;
    map->totalCollectibles = 0;
}

char map_get_tile(t_map *map, int x, int y) {
    if (!map || !map->grid)
        return TILE_WALL;
    
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return TILE_WALL;
    
    return map->grid[y][x];
}

void map_set_tile(t_map *map, int x, int y, char tile) {
    if (!map || !map->grid)
        return;
    
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        map->grid[y][x] = tile;
    }
}

int map_count_collectibles(t_map *map) {
    if (!map || !map->grid)
        return 0;
    
    int count = 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == TILE_COLLECTIBLE) {
                count++;
            }
        }
    }
    
    return count;
}

void map_print(t_map *map) {
    if (!map || !map->grid)
        return;
    
    printf("\n=== MAP ===\n");
    printf("Size: %dx%d\n", map->width, map->height);
    printf("Collectibles: %d\n", map->totalCollectibles);
    printf("Valid: %s\n", map->isValid ? "Yes" : "No");
    printf("Solvable: %s\n", map->isSolvable ? "Yes" : "No");
    printf("\n");
    
    for (int y = 0; y < map->height; y++) {
        printf("%s\n", map->grid[y]);
    }
    
    printf("===========\n\n");
}