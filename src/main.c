#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.h"
#include "map.h"
#include "render.h"
#include "enemy.h"
#include "weather.h"

int map[MAP_SIZE][MAP_SIZE];
double playerX = 3.5, playerY = 3.5, dirX = -1, dirY = 0;
bool showMap = true, keyW = false, keyA = false, keyS = false, keyD = false, isFiring = false, rainActive = false;
GameState gameState = GAME_START;

/**
 * main - Entry point of the game
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <mapfile>\n", argv[0]);
		return (1);
	}

	load_map(argv[1]);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}

	SDL_Window *window = SDL_CreateWindow("3D Maze",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0);
	if (!window)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	init_enemies();
	init_particles();

	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			handle_input(event);
		}

		if (gameState == GAME_RUNNING)
		{
			update_player();
			update_weapon();
			update_enemies();
			update_particles();
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (gameState == GAME_START)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}
		else if (gameState == GAME_RUNNING)
		{
			raycast(renderer);
			if (showMap)
			{
				draw_map(renderer);
			}
			render_enemies(renderer);
			render_particles(renderer);
			draw_weapon(renderer, weaponTexture);
		}
		else if (gameState == GAME_PAUSED)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}
		else if (gameState == GAME_OVER)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}

		SDL_RenderPresent(renderer);
	}

	cleanup(window, renderer);
	return (0);
}
