#include "map.h"
#include <stdio.h>

/**
 * load_map - Loads the map from a file
 * @filename: The name of the map file
 * @map: The map structure
 */
void load_map(const char *filename, Map *map)
{
	FILE *file;
	int x, y;
	char ch;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Could not open map file: %s\n", filename);
		return;
	}

	for (y = 0; y < MAP_SIZE; y++)
	{
		for (x = 0; x < MAP_SIZE; x++)
		{
			fscanf(file, " %c", &ch);
			map->tiles[x][y] = ch - '0';
		}
	}

	fclose(file);
}

/**
 * is_wall - Checks if a position is a wall
 * @map: The map structure
 * @x: The x coordinate
 * @y: The y coordinate
 *
 * Return: true if the position is a wall, false otherwise
 */
bool is_wall(const Map *map, double x, double y)
{
	return (map->tiles[(int)x][(int)y] > 0);
}
