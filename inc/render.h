#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

void draw(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color);
void raycast(SDL_Renderer *renderer);
void draw_map(SDL_Renderer *renderer);
void draw_weapon(SDL_Renderer *renderer, SDL_Texture *texture);

#endif
