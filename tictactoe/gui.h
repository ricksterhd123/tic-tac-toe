#pragma once
#include "board.h"
#include <SDL.h>

void draw_board(board* b, SDL_Renderer* renderer, SDL_Rect* rect);
int get_move(SDL_Rect* rect, int screen_x, int screen_y, int* x, int* y);