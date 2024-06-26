#include "render.h"
#include "game.h"
#include "map.h"
#include <math.h>

/**
 * draw - Draws a rectangle on the screen
 * @renderer: The SDL renderer
 * @x: The x coordinate
 * @y: The y coordinate
 * @w: The width of the rectangle
 * @h: The height of the rectangle
 * @color: The color of the rectangle
 */
void draw(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color)
{
	SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

/**
 * apply_lighting - Applies lighting to a color based on distance
 * @color: The original color
 * @distance: The distance from the player
 *
 * Return: The shaded color
 */
SDL_Color apply_lighting(SDL_Color color, double distance)
{
	double factor = 1.0 / (0.1 * distance + 1.0);
	color.r = (Uint8)(color.r * factor);
	color.g = (Uint8)(color.g * factor);
	color.b = (Uint8)(color.b * factor);
	return (color);
}

/**
 * raycast - Performs raycasting and draws the view
 * @renderer: The SDL renderer
 */
void raycast(SDL_Renderer *renderer)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double distance = (double)x / SCREEN_WIDTH * 20.0;
		SDL_Color color = {255, 255, 255, 255};
		color = apply_lighting(color, distance);
		draw(renderer, x, 0, 1, SCREEN_HEIGHT, color);
	}
}

/**
 * draw_map - Draws the map on the screen
 * @renderer: The SDL renderer
 */
void draw_map(SDL_Renderer *renderer)
{
	for (int y = 0; y < MAP_SIZE; y++)
	{
		for (int x = 0; x < MAP_SIZE; x++)
		{
			SDL_Color color = map[x][y] > 0 ? (SDL_Color){255, 255, 255, 255} : (SDL_Color){0, 0, 0, 255};
			draw(renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
		}
	}
	draw(renderer, playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, (SDL_Color){255, 0, 0, 255});
}

/**
 * draw_weapon - Draws the weapon sprite on the screen
 * @renderer: The SDL renderer
 * @texture: The SDL texture for the weapon
 */
void draw_weapon(SDL_Renderer *renderer, SDL_Texture *texture)
{
	int weaponWidth = 200;
	int weaponHeight = 200;
	int weaponX = (SCREEN_WIDTH - weaponWidth) / 2;
	int weaponY = SCREEN_HEIGHT - weaponHeight - 10;

	SDL_Rect rect = {weaponX, weaponY, weaponWidth, weaponHeight};

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
