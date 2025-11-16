#include "../includes/so_long.h"

void timer_start(t_timer *timer) {
    timer->startTime = GetTime();
    timer->elapsedTime = 0.0;
    timer->running = true;
}

void timer_stop(t_timer *timer) {
    timer->running = false;
}

void timer_update(t_timer *timer) {
    if (timer->running) {
        timer->elapsedTime = GetTime() - timer->startTime;
    }
}

void timer_reset(t_timer *timer) {
    timer->startTime = 0.0;
    timer->elapsedTime = 0.0;
    timer->running = false;
}

char *ft_strdup(const char *s) {
    if (!s)
        return NULL;
    
    size_t len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);
    
    if (!dup)
        return NULL;
    
    size_t i = 0;
    while (i < len) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    
    return dup;
}

size_t ft_strlen(const char *s) {
    size_t len = 0;
    
    if (!s)
        return 0;
    
    while (s[len])
        len++;
    
    return len;
}

void error_exit(const char *message) {
    printf("Error: %s\n", message);
    exit(1);
}

void print_moves(int moves) {
    printf("Moves: %d\n", moves);
}