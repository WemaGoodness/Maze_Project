#ifndef WEATHER_H
#define WEATHER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_PARTICLES 1000

/**
 * struct Particle - Represents a particle for weather effects
 * @x: The x coordinate of the particle
 * @y: The y coordinate of the particle
 * @speed: The speed of the particle
 */
typedef struct Particle
{
	double x;
	double y;
	double speed;
} Particle;

/**
 * struct Weather - Manages the weather effects
 * @particles: Array of particles
 * @rainActive: Flag for rain activation
 */
typedef struct Weather
{
	Particle particles[MAX_PARTICLES];
	bool rainActive;
} Weather;

void init_particles(Weather *weather);
void update_particles(Weather *weather);
void render_particles(Weather *weather, SDL_Renderer *renderer);
void toggle_rain(Weather *weather);

#endif
