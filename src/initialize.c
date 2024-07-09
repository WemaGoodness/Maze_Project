#include "maze.h"
#include <SDL2/SDL_image.h>

/**
 * loadImage - Load a texture from an image file.
 * @texture: Pointer to the texture.
 * @tw: Pointer to the texture width.
 * @th: Pointer to the texture height.
 * @path: Path to the image file.
 */
void loadImage(SDL_Surface** texture, unsigned long* tw, unsigned long* th, const char* path)
{
	*texture = IMG_Load(path); /* Load the image from the given path */
	if (*texture == NULL) {
		fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError()); /* Print error if loading fails */
		exit(1); /* Exit the program */
	}
	*tw = (*texture)->w; /* Get the width of the texture */
	*th = (*texture)->h; /* Get the height of the texture */
}

/**
 * loadTextures - Generate some textures programmatically.
 * @game: Pointer to the game state.
 */
void loadTextures(Game *game)
{
	int texWidth = 64, texHeight = 64; /* Set texture dimensions */
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		game->textures[i] = SDL_CreateRGBSurface(0, texWidth, texHeight, 32, 0, 0, 0, 0); /* Create an RGB surface for the texture */
		if (!game->textures[i])
		{
			fprintf(stderr, "Could not create texture: %s\n", SDL_GetError()); /* Print error if texture creation fails */
			cleanup(game); /* Clean up game resources */
			exit(1); /* Exit the program */
		}
		Uint32* pixels = (Uint32*)game->textures[i]->pixels; /* Get the pixel data of the texture */
		for (int x = 0; x < texWidth; x++)
		{
			for (int y = 0; y < texHeight; y++)
			{
				int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight); /* Calculate XOR color */
				int ycolor = y * 256 / texHeight; /* Calculate Y color */
				int xycolor = y * 128 / texHeight + x * 128 / texWidth; /* Calculate XY color */
				switch (i)
				{
					case 0:
						pixels[texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); /* Assign color to pixel */
						break;
					case 1:
						pixels[texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
						break;
					case 2:
						pixels[texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
						break;
					case 3:
						pixels[texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
						break;
					case 4:
						pixels[texWidth * y + x] = 256 * xorcolor;
						break;
					case 5:
						pixels[texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
						break;
					case 6:
						pixels[texWidth * y + x] = 65536 * ycolor;
						break;
					case 7:
						pixels[texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
						break;
				}
			}
		}
	}
}

/**
 * initialize - Initialize SDL and create window, renderer, and texture.
 * @game: Pointer to the game state.
 */
void initialize(Game *game)
{
	int imgFlags = IMG_INIT_PNG; /* Set the image initialization flags */
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); /* Print error if image initialization fails */
		exit(1); /* Exit the program */
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError()); /* Print error if SDL initialization fails */
		exit(1);
	}

	game->window = SDL_CreateWindow("3D Maze",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN); /* Create the game window */

	/*game->minimap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0);*/

	if (!game->window)
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError()); /* Print error if window creation fails */
		SDL_Quit();
		exit(1);
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED); /* Create the renderer */

	if (!game->renderer)
	{
		fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(game->window);
		SDL_Quit();
		exit(1);
	}

	game->texture = SDL_CreateTexture(game->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT); /* Create the texture */

	if (!game->texture)
	{
		fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(game->renderer);
		SDL_DestroyWindow(game->window);
		SDL_Quit();
		exit(1);
	}

	/*Load image textures*/
	unsigned long tw, th;
	loadImage(&game->textures[0], &tw, &th, "pics/eagle.png");
	loadImage(&game->textures[1], &tw, &th, "pics/redbrick.png");
	loadImage(&game->textures[2], &tw, &th, "pics/purplestone.png");
	loadImage(&game->textures[3], &tw, &th, "pics/greystone.png");
	loadImage(&game->textures[4], &tw, &th, "pics/bluestone.png");
	loadImage(&game->textures[5], &tw, &th, "pics/mossy.png");
	loadImage(&game->textures[6], &tw, &th, "pics/wood.png");
	loadImage(&game->textures[7], &tw, &th, "pics/colorstone.png");
}

/**
 * cleanup - Clean up and quit SDL.
 * @game: Pointer to the game state.
 */
void cleanup(Game *game)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		SDL_FreeSurface(game->textures[i]);
	}
	SDL_DestroyTexture(game->texture);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}
