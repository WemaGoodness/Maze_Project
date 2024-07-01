#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define NUM_TEXTURES 6
#define MAX_PARTICLES 1000

/**
 * struct Game - Struct to hold game state.
 * @posX: Player's X position.
 * @posY: Player's Y position.
 * @dirX: Player's X direction.
 * @dirY: Player's Y direction.
 * @planeX: Camera plane X.
 * @planeY: Camera plane Y.i
 * @pitch: Camera up and down
 * @window: SDL window.
 * @renderer: SDL renderer.
 * @texture: SDL texture.
 * @textures: Array of textures.
 * @running: Game running state.
 * @moveSpeed: Speed of player movement.
 * @rotSpeed: Speed of player rotation.
 */
typedef struct {
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *textures[NUM_TEXTURES];
	bool running;
	double moveSpeed;
	double pitch;
	double rotSpeed;
	int worldMap[MAP_WIDTH][MAP_HEIGHT];
} Game;

/**
 * struct Particle - Struct to hold particle state for weather effects.
 * @x: Particle's X position.
 * @y: Particle's Y position.
 * @speed: Particle's speed.
 */
typedef struct {
	int x, y;
	double speed;
} Particle;

/**
 * struct Weather - Struct to hold weather state.
 * @particles: Array of particles.
 * @rainActive: Rain effect state.
 */
typedef struct {
	Particle particles[MAX_PARTICLES];
	bool rainActive;
} Weather;

void initialize(Game *game);
void loadTextures(Game *game);
void handleInput(Game *game, Weather *weather);
void update(Weather *weather);
void render(Game *game, Weather *weather);
void cleanup(Game *game);
void performRaycasting(Game *game, Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void drawBuffer(Game *game, Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void init_particles(Weather *weather);
void update_particles(Weather *weather);
void render_particles(Weather *weather, SDL_Renderer *renderer);
void toggle_rain(Weather *weather);

#endif
