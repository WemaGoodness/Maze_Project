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

/**
 * drawMinimap - Draw a minimap for the game.
 * @game: Pointer to the game state.
 *
 * This function draws a minimap on an SDL_Surface. The minimap is a top-down
 * view of the game world, with walls represented as black blocks and open spaces
 * as white blocks. The player's position is marked with a red block, and the
 * player's direction is indicated by a blue line.
 */
/*void drawMinimap(Game *game)
{
	double dirAngle = atan2(game->dirY, game->dirX);
	SDL_FillRect(game->minimap, NULL, SDL_MapRGB(game->minimap->format, 255, 255, 255));

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++) {
			if (game->worldMap[x][y] > 0) {
				SDL_Rect rect = {x * MINIMAP_SCALE, y * MINIMAP_SCALE, MINIMAP_SCALE, MINIMAP_SCALE};
				SDL_FillRect(game->minimap, &rect, SDL_MapRGB(game->minimap->format, 0, 0, 0));
			}
		}
	}

	SDL_Rect playerRect = {(int)game->posX * MINIMAP_SCALE, (int)game->posY * MINIMAP_SCALE, MINIMAP_SCALE, MINIMAP_SCALE};
	SDL_FillRect(game->minimap, &playerRect, SDL_MapRGB(game->minimap->format, 0, 0, 255));

	SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(game->minimap);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = -30; i <= 30; i++)
	{
		double angle = dirAngle + i * M_PI / 180.0;
		double endX = game->posX + cos(angle) * 5.0;
		double endY = game->posY + sin(angle) * 5.0;
		SDL_RenderDrawLine(renderer, game->posX * MINIMAP_SCALE, game->posY * MINIMAP_SCALE,
				endX * MINIMAP_SCALE, endY * MINIMAP_SCALE);
	}
	SDL_DestroyRenderer(renderer);
}*/
