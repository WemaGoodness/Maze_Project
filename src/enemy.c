#include "enemy.h"
#include "game.h"
#include "render.h"
#include "map.h"

Enemy enemies[10];
int numEnemies = 0;

/**
 * init_enemies - Initializes enemies with positions and textures
 */
void init_enemies(void)
{
    enemies[0].x = 4.5;
    enemies[0].y = 4.5;
    enemies[0].dirX = 0;
    enemies[0].dirY = 1;
    enemies[0].color = (SDL_Color){255, 0, 0, 255};
    numEnemies = 1;
}

/**
 * update_enemies - Updates the positions of enemies based on simple AI
 */
void update_enemies(void)
{
    for (int i = 0; i < numEnemies; i++)
    {
        double dx = playerX - enemies[i].x;
        double dy = playerY - enemies[i].y;
        double dist = sqrt(dx * dx + dy * dy);
        dx /= dist;
        dy /= dist;

        move_enemy(&enemies[i], dx * 0.02, dy * 0.02);
    }
}

/**
 * render_enemies - Renders the enemies on the screen
 * @renderer: The SDL renderer
 */
void render_enemies(SDL_Renderer *renderer)
{
    for (int i = 0; i < numEnemies; i++)
    {
        int enemyX = (int)(enemies[i].x * TILE_SIZE);
        int enemyY = (int)(enemies[i].y * TILE_SIZE);
        draw(renderer, enemyX, enemyY, TILE_SIZE, TILE_SIZE, enemies[i].color);
    }
}

/**
 * move_enemy - Moves an enemy if the new position is not a wall
 * @enemy: The enemy to move
 * @dx: The change in x position
 * @dy: The change in y position
 */
void move_enemy(Enemy *enemy, double dx, double dy)
{
    if (!is_wall(enemy->x + dx, enemy->y))
    {
        enemy->x += dx;
    }
    if (!is_wall(enemy->x, enemy->y + dy))
    {
        enemy->y += dy;
    }
}
