#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.h"
#include "map.h"
#include "render.h"
#include "enemy.h"
#include "weather.h"

/**
 * main - Entry point of the game
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	Game game;
	EnemyManager enemyManager;
	Weather weather;
	Map map;
	SDL_Event event;
	bool running = true;

	if (argc < 2)
	{
		printf("Usage: %s <mapfile>\n", argv[0]);
		return 1;
	}

	load_map(argv[1], &map);
	game.map = &map;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("3D Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	game.playerX = 3.5;
	game.playerY = 3.5;
	game.dirX = -1;
	game.dirY = 0;
	game.showMap = true;
	game.keyW = false;
	game.keyA = false;
	game.keyS = false;
	game.keyD = false;
	game.isFiring = false;
	game.rainActive = false;
	game.weaponTexture = NULL;
	game.gameState = GAME_RUNNING;

	init_enemies(&enemyManager);
	init_particles(&weather);

	printf("Initialization complete. Entering main loop.\n");

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			handle_input(event, &game);
		}

		if (game.gameState == GAME_RUNNING)
		{
			update_player(&game);
			update_weapon(&game);
			update_enemies(&enemyManager, game.playerX, game.playerY, game.map);
			update_particles(&weather);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (game.gameState == GAME_START)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}
		else if (game.gameState == GAME_RUNNING)
		{
			raycast(renderer, &game);
			if (game.showMap)
			{
				draw_map(renderer, &map, &game);
			}
			render_enemies(&enemyManager, renderer);
			render_particles(&weather, renderer);
			draw_weapon(renderer, game.weaponTexture);
		}
		else if (game.gameState == GAME_PAUSED)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}
		else if (game.gameState == GAME_OVER)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
		}

		SDL_RenderPresent(renderer);
	}

	printf("Exiting main loop.\n");

	cleanup(window, renderer, &game);
	return 0;
}

