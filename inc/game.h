#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 64

typedef enum GameState
{
	GAME_START,
	GAME_RUNNING,
	GAME_PAUSED,
	GAME_OVER
} GameState;

extern double playerX, playerY, dirX, dirY;
extern bool showMap, keyW, keyA, keyS, keyD, isFiring, rainActive;
extern SDL_Texture *weaponTexture;
extern GameState gameState;

void handle_input(SDL_Event event);
void update_player(void);
void toggle_map(void);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);
void fire_weapon(void);
void update_weapon(void);
void change_game_state(GameState newState);

#endif
