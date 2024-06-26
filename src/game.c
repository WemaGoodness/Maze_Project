#include "game.h"
#include "player.h"
#include "render.h"
#include "weather.h"
#include "enemy.h"

SDL_Texture *weaponTexture = NULL;
bool isFiring = false;
GameState gameState = GAME_START;

/**
 * handle_input - Handles user input
 * @event: The SDL event
 */
void handle_input(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				/* Rotate camera left */
				break;
			case SDLK_RIGHT:
				/* Rotate camera right */
				break;
			case SDLK_w:
				keyW = true;
				break;
			case SDLK_s:
				keyS = true;
				break;
			case SDLK_a:
				keyA = true;
				break;
			case SDLK_d:
				keyD = true;
				break;
			case SDLK_m:
				toggle_map();
				break;
			case SDLK_SPACE:
				isFiring = true;
				fire_weapon();
				break;
			case SDLK_p:
				if (gameState == GAME_RUNNING)
				{
					change_game_state(GAME_PAUSED);
				}
				else if (gameState == GAME_PAUSED)
				{
					change_game_state(GAME_RUNNING);
				}
				break;
			case SDLK_r:
				if (gameState == GAME_OVER)
				{
					change_game_state(GAME_START);
				}
				break;
			case SDLK_RETURN:
				if (gameState == GAME_START)
				{
					change_game_state(GAME_RUNNING);
				}
				break;
			case SDLK_ESCAPE:
				if (gameState == GAME_RUNNING)
				{
					change_game_state(GAME_PAUSED);
				}
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				keyW = false;
				break;
			case SDLK_s:
				keyS = false;
				break;
			case SDLK_a:
				keyA = false;
				break;
			case SDLK_d:
				keyD = false;
				break;
			case SDLK_SPACE:
				isFiring = false;
				break;
		}
	}
}

/**
 * update_player - Updates player position based on input
 */
void update_player(void)
{
	if (keyW && !keyS)
	{
		move_player(dirX * 0.1, dirY * 0.1);
	}
	else if (keyS && !keyW)
	{
		move_player(-dirX * 0.1, -dirY * 0.1);
	}
	if (keyA && !keyD)
	{
		/* Strafe camera left */
	}
	else if (keyD && !keyA)
	{
		/* Strafe camera right */
	}
}

/**
 * toggle_map - Toggles the map display
 */
void toggle_map(void)
{
	showMap = !showMap;
}

/**
 * cleanup - Cleans up SDL resources
 * @window: The SDL window
 * @renderer: The SDL renderer
 */
void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
	if (weaponTexture)
	{
		SDL_DestroyTexture(weaponTexture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * fire_weapon - Simulates firing the weapon
 */
void fire_weapon(void)
{
	// Placeholder for weapon firing logic
	printf("Weapon fired!\n");
}

/**
 * update_weapon - Updates the weapon state (animation, etc.)
 */
void update_weapon(void)
{
	if (isFiring)
	{
		// Placeholder for weapon animation update
	}
}

/**
 * change_game_state - Changes the current game state
 * @newState: The new game state
 */
void change_game_state(GameState newState)
{
	gameState = newState;
}
