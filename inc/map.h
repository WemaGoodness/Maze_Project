#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAP_SIZE 10

extern int map[MAP_SIZE][MAP_SIZE];

void load_map(const char *filename);
bool is_wall(double x, double y);

#endif
