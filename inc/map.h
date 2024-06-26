#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAP_SIZE 10

/**
 * struct Map - Represents the map of the game
 * @tiles: 2D array representing the tiles of the map
 */
typedef struct Map
{
	int tiles[MAP_SIZE][MAP_SIZE];
} Map;

void load_map(const char *filename, Map *map);
bool is_wall(const Map *map, double x, double y);

#endif
