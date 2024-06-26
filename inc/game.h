#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "map.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 64

/**
 * enum GameState - Represents the state of the game
 * @GAME_START: The game start state
 * @GAME_RUNNING: The game running state
 * @GAME_PAUSED: The game paused state
 * @GAME_OVER: The game over state
 */
typedef enum GameState
{
	GAME_START,
	GAME_RUNNING,
	GAME_PAUSED,
	GAME_OVER
} GameState;

/**
 * struct Game - Represents the game state
 * @playerX: The x coordinate of the player
 * @playerY: The y coordinate of the player
 * @dirX: The direction in the x axis
 * @dirY: The direction in the y axis
 * @showMap: Flag to show the map
 * @keyW: Flag for W key press
 * @keyA: Flag for A key press
 * @keyS: Flag for S key press
 * @keyD: Flag for D key press
 * @isFiring: Flag for firing
 * @rainActive: Flag for rain activation
 * @weaponTexture: The texture of the weapon
 * @gameState: The current game state
 * @map: Pointer to the current map
 */
typedef struct Game
{
	double playerX;
	double playerY;
	double dirX;
	double dirY;
	bool showMap;
	bool keyW;
	bool keyA;
	bool keyS;
	bool keyD;
	bool isFiring;
	bool rainActive;
	SDL_Texture *weaponTexture;
	GameState gameState;
	Map *map;
} Game;

void handle_input(SDL_Event event, Game *game);
void update_player(Game *game);
void toggle_map(Game *game);
void cleanup(SDL_Window *window, SDL_Renderer *renderer, Game *game);
void fire_weapon(Game *game);
void update_weapon(Game *game);
void change_game_state(Game *game, GameState newState);

#endif
