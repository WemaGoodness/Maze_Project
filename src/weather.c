#include "weather.h"
#include "game.h"
#include <stdlib.h>

Particle particles[MAX_PARTICLES];
bool rainActive = false;

/**
 * init_particles - Initializes the particles for rain
 */
void init_particles(void)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
        particles[i].speed = 2 + rand() % 5;
    }
}

/**
 * update_particles - Updates the positions of the particles
 */
void update_particles(void)
{
    if (!rainActive)
    {
        return;
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].y += particles[i].speed;
        if (particles[i].y > SCREEN_HEIGHT)
        {
            particles[i].x = rand() % SCREEN_WIDTH;
            particles[i].y = 0;
        }
    }
}

/**
 * render_particles - Renders the particles on the screen
 * @renderer: The SDL renderer
 */
void render_particles(SDL_Renderer *renderer)
{
    if (!rainActive)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        SDL_RenderDrawPoint(renderer, (int)particles[i].x, (int)particles[i].y);
    }
}

/**
 * toggle_rain - Toggles the rain effect
 */
void toggle_rain(void)
{
    rainActive = !rainActive;
    if (rainActive)
    {
        init_particles();
    }
}
