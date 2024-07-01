#include "maze.h"
#include "weather.h"

/**
 * handleInput - Handle user input.
 * @game: Pointer to the game state.
 * @weather: Pointer to the weather state.
 *
 * This function handles the user input for the game. It processes
 * keyboard events for player movement and rotation, as well as
 * toggling the rain effect.
 */
void handleInput(Game *game, Weather *weather)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game->running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					game->running = false;
					break;
				case SDLK_r:
					toggle_rain(weather);
					break;
				case SDLK_UP:
					game->pitch += 1;
					break;
				case SDLK_DOWN:
					game->pitch -= 1;
					break;
				default:
					break;
			}
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	game->moveSpeed = (state[SDL_SCANCODE_LSHIFT]) ? 0.1 : 0.05;

	if (state[SDL_SCANCODE_W])
	{
		if (game->worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)game->posY] == 0)
			game->posX += game->dirX * game->moveSpeed;
		if (game->worldMap[(int)game->posX][(int)(game->posY + game->dirY * game->moveSpeed)] == 0)
			game->posY += game->dirY * game->moveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (game->worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)game->posY] == 0)
			game->posX -= game->dirX * game->moveSpeed;
		if (game->worldMap[(int)game->posX][(int)(game->posY - game->dirY * game->moveSpeed)] == 0)
			game->posY -= game->dirY * game->moveSpeed;
	}
	if (state[SDL_SCANCODE_D])
	{
		if (game->worldMap[(int)(game->posX + game->dirY * game->moveSpeed)][(int)game->posY] == 0)
			game->posX += game->dirY * game->moveSpeed;
		if (game->worldMap[(int)game->posX][(int)(game->posY - game->dirX * game->moveSpeed)] == 0)
			game->posY -= game->dirX * game->moveSpeed;
	}
	if (state[SDL_SCANCODE_A])
	{
		if (game->worldMap[(int)(game->posX - game->dirY * game->moveSpeed)][(int)game->posY] == 0)
			game->posX -= game->dirY * game->moveSpeed;
		if (game->worldMap[(int)game->posX][(int)(game->posY + game->dirX * game->moveSpeed)] == 0)
			game->posY += game->dirX * game->moveSpeed;
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
		game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}
}
