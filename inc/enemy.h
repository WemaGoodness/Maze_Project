#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "map.h"

/**
 * struct Enemy - Represents an enemy in the game
 * @x: The x coordinate of the enemy
 * @y: The y coordinate of the enemy
 * @dirX: The direction in the x axis
 * @dirY: The direction in the y axis
 * @color: The color of the enemy
 */
typedef struct Enemy
{
	double x;
	double y;
	double dirX;
	double dirY;
	SDL_Color color;
} Enemy;

/**
 * struct EnemyManager - Manages the collection of enemies
 * @enemies: Array of enemies
 * @numEnemies: Number of enemies
 */
typedef struct EnemyManager
{
	Enemy enemies[10];
	int numEnemies;
} EnemyManager;

void init_enemies(EnemyManager *enemyManager);
void update_enemies(EnemyManager *enemyManager, double playerX, double playerY, Map *map);
void render_enemies(EnemyManager *enemyManager, SDL_Renderer *renderer);
void move_enemy(Enemy *enemy, double dx, double dy, Map *map);

#endif
