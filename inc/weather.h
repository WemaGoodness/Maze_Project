#ifndef WEATHER_H
#define WEATHER_H

#include "maze.h"

void init_particles(Weather *weather);
void update_particles(Weather *weather);
void render_particles(Weather *weather, SDL_Renderer *renderer);
void toggle_rain(Weather *weather);

#endif
