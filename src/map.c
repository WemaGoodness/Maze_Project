#include "map.h"
#include <stdio.h>

int map[MAP_SIZE][MAP_SIZE];

/**
 * load_map - Loads the map from a file
 * @filename: The name of the map file
 */
void load_map(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Could not open map file: %s\n", filename);
		return;
	}

	for (int y = 0; y < MAP_SIZE; y++)
	{
		for (int x = 0; x < MAP_SIZE; x++)
		{
			char ch;
			fscanf(file, " %c", &ch);
			map[x][y] = ch - '0';
		}
	}

	fclose(file);
}

/**
 * is_wall - Checks if a position is a wall
 * @x: The x coordinate
 * @y: The y coordinate
 *
 * Return: true if the position is a wall, false otherwise
 */
bool is_wall(double x, double y)
{
	return (map[(int)x][(int)y] > 0); // Use the casted values directly
}
