#include "player.h"
#include "map.h"
#include "game.h"

/**
 * move_player - Moves the player
 * @dx: The change in x position
 * @dy: The change in y position
 */
void move_player(double dx, double dy)
{
	if (!is_wall(playerX + dx, playerY))
	{
		playerX += dx;
	}
	if (!is_wall(playerX, playerY + dy))
	{
		playerY += dy;
	}
}
