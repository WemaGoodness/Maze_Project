#include "weather.h"
#include "maze.h"
#include <stdlib.h>

/**
 * init_particles - Initializes particles for weather effects
 * @weather: The weather structure
 */
void init_particles(Weather *weather)
{
	int i;

	for (i = 0; i < MAX_PARTICLES; i++)
	{
		weather->particles[i].x = rand() % SCREEN_WIDTH;
		weather->particles[i].y = rand() % SCREEN_HEIGHT;
		weather->particles[i].speed = (rand() % 5 + 1) / 10.0;
	}
}

/**
 * update_particles - Updates the position of particles
 * @weather: The weather structure
 */
void update_particles(Weather *weather)
{
	int i;

	for (i = 0; i < MAX_PARTICLES; i++)
	{
		weather->particles[i].y += weather->particles[i].speed;
		if (weather->particles[i].y > SCREEN_HEIGHT)
		{
			weather->particles[i].y = 0;
			weather->particles[i].x = rand() % SCREEN_WIDTH;
		}
	}
}

/**
 * render_particles - Renders particles on the screen
 * @weather: The weather structure
 * @renderer: The SDL renderer
 */
void render_particles(Weather *weather, SDL_Renderer *renderer)
{
	int i;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	for (i = 0; i < MAX_PARTICLES; i++)
	{
		SDL_RenderDrawPoint(renderer, weather->particles[i].x, weather->particles[i].y);
	}
}

/**
 * toggle_rain - Toggles rain effect on or off
 * @weather: The weather structure
 */
void toggle_rain(Weather *weather)
{
	weather->rainActive = !weather->rainActive;
}
