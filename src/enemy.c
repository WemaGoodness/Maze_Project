#include "enemy.h"
#include "render.h"
#include "map.h"
#include <math.h>

/**
 * init_enemies - Initializes enemies with positions and textures
 * @enemyManager: The enemy manager
 */
void init_enemies(EnemyManager *enemyManager)
{
	enemyManager->enemies[0].x = 4.5;
	enemyManager->enemies[0].y = 4.5;
	enemyManager->enemies[0].dirX = 0;
	enemyManager->enemies[0].dirY = 1;
	enemyManager->enemies[0].color = (SDL_Color){255, 0, 0, 255};
	enemyManager->numEnemies = 1;
}

/**
 * update_enemies - Updates the positions of enemies based on simple AI
 * @enemyManager: The enemy manager
 * @playerX: The x coordinate of the player
 * @playerY: The y coordinate of the player
 * @map: The map structure
 */
void update_enemies(EnemyManager *enemyManager, double playerX, double playerY, Map *map)
{
	int i;
	double dx, dy, dist;

	for (i = 0; i < enemyManager->numEnemies; i++)
	{
		dx = playerX - enemyManager->enemies[i].x;
		dy = playerY - enemyManager->enemies[i].y;
		dist = sqrt(dx * dx + dy * dy);
		dx /= dist;
		dy /= dist;

		move_enemy(&enemyManager->enemies[i], dx * 0.02, dy * 0.02, map);
	}
}

/**
 * render_enemies - Renders the enemies on the screen
 * @enemyManager: The enemy manager
 * @renderer: The SDL renderer
 */
void render_enemies(EnemyManager *enemyManager, SDL_Renderer *renderer)
{
	int i, enemyX, enemyY;

	for (i = 0; i < enemyManager->numEnemies; i++)
	{
		enemyX = (int)(enemyManager->enemies[i].x * TILE_SIZE);
		enemyY = (int)(enemyManager->enemies[i].y * TILE_SIZE);
		draw(renderer, enemyX, enemyY, TILE_SIZE, TILE_SIZE, enemyManager->enemies[i].color);
	}
}

/**
 * move_enemy - Moves an enemy if the new position is not a wall
 * @enemy: The enemy to move
 * @dx: The change in x position
 * @dy: The change in y position
 * @map: The map structure
 */
void move_enemy(Enemy *enemy, double dx, double dy, Map *map)
{
	if (!is_wall(map, enemy->x + dx, enemy->y))
	{
		enemy->x += dx;
	}
	if (!is_wall(map, enemy->x, enemy->y + dy))
	{
		enemy->y += dy;
	}
}
