#ifndef WEATHER_H
#define WEATHER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_PARTICLES 1000

typedef struct Particle
{
        double x, y, speed;
} Particle;

extern Particle particles[MAX_PARTICLES];

void init_particles(void);
void update_particles(void);
void render_particles(SDL_Renderer *renderer);
void toggle_rain(void);

#endif
