#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "game.h"
#include "map.h"

/**
 * move_player - Moves the player
 * @game: The game state
 * @map: The map structure
 * @dx: The change in x position
 * @dy: The change in y position
 *
 * This function updates the player's position based on the provided deltas (dx, dy).
 * It also checks if the new position is a wall using the provided map.
 */
void move_player(Game *game, const Map *map, double dx, double dy);

#endif
