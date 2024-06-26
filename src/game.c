#include "game.h"
#include "player.h"
#include "render.h"
#include "weather.h"
#include "enemy.h"

/**
 * handle_input - Handles user input
 * @event: The SDL event
 * @game: The game state
 */
void handle_input(SDL_Event event, Game *game)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_w:
				game->keyW = true;
				break;
			case SDLK_s:
				game->keyS = true;
				break;
			case SDLK_a:
				game->keyA = true;
				break;
			case SDLK_d:
				game->keyD = true;
				break;
			case SDLK_m:
				toggle_map(game);
				break;
			case SDLK_SPACE:
				game->isFiring = true;
				fire_weapon(game);
				break;
			case SDLK_p:
				if (game->gameState == GAME_RUNNING)
				{
					change_game_state(game, GAME_PAUSED);
				}
				else if (game->gameState == GAME_PAUSED)
				{
					change_game_state(game, GAME_RUNNING);
				}
				break;
			case SDLK_r:
				if (game->gameState == GAME_OVER)
				{
					change_game_state(game, GAME_START);
				}
				break;
			case SDLK_RETURN:
				if (game->gameState == GAME_START)
				{
					change_game_state(game, GAME_RUNNING);
				}
				break;
			case SDLK_ESCAPE:
				if (game->gameState == GAME_RUNNING)
				{
					change_game_state(game, GAME_PAUSED);
				}
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				game->keyW = false;
				break;
			case SDLK_s:
				game->keyS = false;
				break;
			case SDLK_a:
				game->keyA = false;
				break;
			case SDLK_d:
				game->keyD = false;
				break;
			case SDLK_SPACE:
				game->isFiring = false;
				break;
		}
	}
}

/**
 * update_player - Updates player position based on input
 * @game: The game state
 *
 * This function updates the player's position based on the current key presses.
 * It calls the move_player function with the appropriate deltas based on the key presses.
 */
void update_player(Game *game)
{
	if (game->keyW && !game->keyS)
	{
		move_player(game, game->map, game->dirX * 0.1, game->dirY * 0.1);
	}
	else if (game->keyS && !game->keyW)
	{
		move_player(game, game->map, -game->dirX * 0.1, -game->dirY * 0.1);
	}
	if (game->keyA && !game->keyD)
	{
		/* Strafe camera left */
	}
	else if (game->keyD && !game->keyA)
	{
		/* Strafe camera right */
	}
}

/**
 * toggle_map - Toggles the map display
 * @game: The game state
 */
void toggle_map(Game *game)
{
	game->showMap = !game->showMap;
}

/**
 * cleanup - Cleans up SDL resources
 * @window: The SDL window
 * @renderer: The SDL renderer
 * @game: The game state
 */
void cleanup(SDL_Window *window, SDL_Renderer *renderer, Game *game)
{
	if (game->weaponTexture)
	{
		SDL_DestroyTexture(game->weaponTexture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * fire_weapon - Simulates firing the weapon
 * @game: The game state
 *
 * This function simulates firing the weapon by printing a message to the console.
 * It also sets the isFiring flag to true.
 */
void fire_weapon(Game *game)
{
	game->isFiring = true;

	printf("Weapon fired!\n");
}

/**
 * update_weapon - Updates the weapon state (animation, etc.)
 * @game: The game state
 */
void update_weapon(Game *game)
{
	if (game->isFiring)
	{
		/* Placeholder for weapon animation update */
	}
}

/**
 * change_game_state - Changes the current game state
 * @game: The game state
 * @newState: The new game state
 */
void change_game_state(Game *game, GameState newState)
{
	game->gameState = newState;
}
