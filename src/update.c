#include "maze.h"
#include "weather.h"

/**
 * update - Update the game state.
 * @game: Pointer to the game state.
 * @weather: Pointer to the weather state.
 */
void update(Weather *weather)
{
	if (weather->rainActive)
	{
		update_particles(weather);
	}
}
