#include "../includes/so_long.h"

void animation_init(t_animation *anim, float speed) {
    if (!anim)
        return;
    
    anim->currentFrame = 0;
    anim->frameTimer = 0.0f;
    anim->frameSpeed = speed;
    
    // Inicializar frames como vazios
    for (int i = 0; i < ANIMATION_FRAMES; i++) {
        anim->frames[i].id = 0;
        anim->frames[i].width = 0;
        anim->frames[i].height = 0;
    }
}

void animation_update(t_animation *anim) {
    if (!anim)
        return;
    
    anim->frameTimer += GetFrameTime();
    
    if (anim->frameTimer >= anim->frameSpeed) {
        anim->frameTimer = 0.0f;
        anim->currentFrame = (anim->currentFrame + 1) % ANIMATION_FRAMES;
    }
}

void animation_draw(t_animation *anim, int x, int y) {
    if (!anim || anim->frames[anim->currentFrame].id == 0)
        return;
    
    DrawTexture(anim->frames[anim->currentFrame], x, y, WHITE);
}

void player_animation_update(t_player *player) {
    if (!player)
        return;
    
    animation_update(&player->animation);
}

void enemy_animation_update(t_enemy *enemy) {
    if (!enemy || !enemy->active)
        return;
    
    animation_update(&enemy->animation);
}