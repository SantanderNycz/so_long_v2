#include "../includes/so_long.h"

Texture2D create_colored_texture(int width, int height, Color color) {
    Image img = GenImageColor(width, height, color);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

Texture2D load_texture_safe(const char *filepath, Color fallbackColor, int width, int height) {
    Texture2D texture;
    
    if (FileExists(filepath)) {
        Image img = LoadImage(filepath);
        ImageResize(&img, width, height);
        texture = LoadTextureFromImage(img);
        UnloadImage(img);
        printf("[OK] Loaded: %s\n", filepath);
    } else {
        printf("[WARNING] File not found: %s (using fallback)\n", filepath);
        texture = create_colored_texture(width, height, fallbackColor);
    }
    
    return texture;
}

void load_player_textures(t_game *game) {
    const char *playerPath = "assets/player.png";
    
    if (FileExists(playerPath)) {
        Image img = LoadImage(playerPath);
        ImageResize(&img, TILE_SIZE - 10, TILE_SIZE - 10);
        
        for (int i = 0; i < ANIMATION_FRAMES; i++) {
            game->textures.player[i] = LoadTextureFromImage(img);
            game->player.animation.frames[i] = game->textures.player[i];
        }
        
        UnloadImage(img);
        printf("[OK] Loaded player sprite\n");
    } else {
        printf("[WARNING] Player sprite not found, using solid color\n");
        for (int i = 0; i < ANIMATION_FRAMES; i++) {
            game->textures.player[i] = create_colored_texture(TILE_SIZE - 10, TILE_SIZE - 10, BLUE);
            game->player.animation.frames[i] = game->textures.player[i];
        }
    }
    
    animation_init(&game->player.animation, ANIMATION_SPEED);
}

void load_enemy_textures(t_game *game) {
    // Carregar 3 frames diferentes para o inimigo
    const char *enemyPaths[3] = {
        "assets/enemy1.png",
        "assets/enemy2.png",
        "assets/enemy3.png"
    };
    
    bool anyLoaded = false;
    
    for (int i = 0; i < ENEMY_ANIMATION_FRAMES; i++) {
        if (FileExists(enemyPaths[i])) {
            Image img = LoadImage(enemyPaths[i]);
            ImageResize(&img, TILE_SIZE - 10, TILE_SIZE - 10);
            game->textures.enemy[i] = LoadTextureFromImage(img);
            UnloadImage(img);
            printf("[OK] Loaded enemy frame %d\n", i + 1);
            anyLoaded = true;
        } else {
            // Fallback: cores diferentes para cada frame
            Color colors[3] = {RED, (Color){255, 50, 50, 255}, (Color){200, 0, 0, 255}};
            game->textures.enemy[i] = create_colored_texture(TILE_SIZE - 10, TILE_SIZE - 10, colors[i]);
            if (!anyLoaded && i == 0) {
                printf("[WARNING] Enemy sprites not found, using solid colors\n");
            }
        }
    }
    
    // Atribuir aos inimigos
    for (int j = 0; j < game->enemyCount; j++) {
        for (int i = 0; i < ENEMY_ANIMATION_FRAMES; i++) {
            game->enemies[j].animation.frames[i] = game->textures.enemy[i];
        }
        game->enemies[j].animation.currentFrame = 0;
        game->enemies[j].animation.frameTimer = 0.0f;
        game->enemies[j].animation.frameSpeed = 1.0f; // 1 segundo por frame
    }
}

void load_collectible_textures(t_game *game) {
    // Carregar 3 frames: normal, coletando (2s), coletado
    const char *collectiblePaths[3] = {
        "assets/collectible1.png",  // Frame 1: normal
        "assets/collectible2.png",  // Frame 2: animação ao coletar
        "assets/collectible3.png"   // Frame 3: estado final após coletar
    };
    
    bool anyLoaded = false;
    
    for (int i = 0; i < COLLECTIBLE_ANIMATION_FRAMES; i++) {
        if (FileExists(collectiblePaths[i])) {
            Image img = LoadImage(collectiblePaths[i]);
            ImageResize(&img, TILE_SIZE - 20, TILE_SIZE - 20);
            game->textures.collectible[i] = LoadTextureFromImage(img);
            UnloadImage(img);
            printf("[OK] Loaded collectible frame %d\n", i + 1);
            anyLoaded = true;
        } else {
            // Fallback
            Color colors[3] = {GOLD, ORANGE, (Color){150, 150, 150, 255}};
            game->textures.collectible[i] = create_colored_texture(TILE_SIZE - 20, TILE_SIZE - 20, colors[i]);
            if (!anyLoaded && i == 0) {
                printf("[WARNING] Collectible sprites not found, using solid colors\n");
            }
        }
    }
}

void load_textures(t_game *game) {
    if (!game)
        return;
    
    printf("\n=== Loading Textures ===\n");
    
    game->textures.wall = load_texture_safe("assets/wall.png", DARKGRAY, TILE_SIZE, TILE_SIZE);
    game->textures.floor = load_texture_safe("assets/floor.png", LIGHTGRAY, TILE_SIZE, TILE_SIZE);
    game->textures.exit_closed = load_texture_safe("assets/exit_close.png", GRAY, TILE_SIZE - 10, TILE_SIZE - 10);
    game->textures.exit_open = load_texture_safe("assets/exit_open.png", GREEN, TILE_SIZE - 10, TILE_SIZE - 10);
    
    load_collectible_textures(game);
    load_player_textures(game);
    load_enemy_textures(game);
    
    game->font = GetFontDefault();
    
    printf("========================\n\n");
}

void unload_textures(t_game *game) {
    if (!game)
        return;
    
    if (game->textures.wall.id > 0) UnloadTexture(game->textures.wall);
    if (game->textures.floor.id > 0) UnloadTexture(game->textures.floor);
    if (game->textures.exit_closed.id > 0) UnloadTexture(game->textures.exit_closed);
    if (game->textures.exit_open.id > 0) UnloadTexture(game->textures.exit_open);
    
    for (int i = 0; i < ANIMATION_FRAMES; i++) {
        if (game->textures.player[i].id > 0)
            UnloadTexture(game->textures.player[i]);
    }
    
    for (int i = 0; i < ENEMY_ANIMATION_FRAMES; i++) {
        if (game->textures.enemy[i].id > 0)
            UnloadTexture(game->textures.enemy[i]);
    }
    
    for (int i = 0; i < COLLECTIBLE_ANIMATION_FRAMES; i++) {
        if (game->textures.collectible[i].id > 0)
            UnloadTexture(game->textures.collectible[i]);
    }
    
    printf("Textures unloaded\n");
}