#include "maze.h"

/**
 * performRaycasting - Perform raycasting to calculate visible walls.
 * @game: Pointer to the game state.
 * @buffer: The buffer containing the pixel data.
 */
void performRaycasting(Game *game, Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	int x;
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double rayDirX = game->dirX + game->planeX * cameraX;
		double rayDirY = game->dirY + game->planeY * cameraX;
		int mapX = (int)game->posX;
		int mapY = (int)game->posY;
		double sideDistX, sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int stepX, stepY, hit = 0, side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		int texNum = game->worldMap[mapX][mapY] - 1;
		double wallX;
		if (side == 0)
			wallX = game->posY + perpWallDist * rayDirY;
		else
			wallX = game->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)TEX_WIDTH);
		if (side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;

		double step = 1.0 * TEX_HEIGHT / lineHeight;
		double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			Uint32 color = ((Uint32 *)game->textures[texNum]->pixels)[TEX_HEIGHT * texY + texX];
			if (side == 1)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
		}

		for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++)
		{
			Uint32 floorColor = 0x654321;
			Uint32 ceilingColor = 0x87CEEB;

			buffer[y][x] = floorColor;
			buffer[SCREEN_HEIGHT - y - 1][x] = ceilingColor;
		}

	}
}
