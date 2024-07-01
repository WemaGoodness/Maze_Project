#include "maze.h"
#include "weather.h"

/**
 * drawBuffer - Draw the buffer to the screen.
 * @game: Pointer to the game state.
 * @buffer: The buffer containing the pixel data.
 */
void drawBuffer(Game *game, Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	SDL_UpdateTexture(game->texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(game->renderer);
	SDL_RenderCopy(game->renderer, game->texture, NULL, NULL);
	SDL_RenderPresent(game->renderer);
}

/**
 * render - Render the game frame.
 * @game: Pointer to the game state.
 * @weather: Pointer to the weather state.
 */
void render(Game *game, Weather *weather)
{
	Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};
	performRaycasting(game, buffer);
	drawBuffer(game, buffer);
	if (weather->rainActive)
	{
		render_particles(weather, game->renderer);
	}
}
