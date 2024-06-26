#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

typedef struct Enemy
{
    double x, y;
    double dirX, dirY;
    SDL_Color color;
} Enemy;

extern Enemy enemies[10];
extern int numEnemies;

void init_enemies(void);
void update_enemies(void);
void render_enemies(SDL_Renderer *renderer);
void move_enemy(Enemy *enemy, double dx, double dy);

#endif
