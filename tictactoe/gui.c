#pragma once
#include "gui.h"

void draw_cross(SDL_Renderer* renderer, int x, int y, int w, int h, int padding)
{
	SDL_RenderDrawLine(renderer, x + padding, y + padding, x + w - padding, y + h - padding);
	SDL_RenderDrawLine(renderer, x + padding, y + h - padding, x + w - padding, y + padding);
}

void plot(SDL_Renderer* renderer, int x, int y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

void draw_naught(SDL_Renderer* renderer, int x0, int y0, int w, int h, int padding)
{
	x0 = x0 + w / 2;
	y0 = y0 + h / 2;
	int radius = (w + h - 2 * padding) / 4;
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	plot(renderer, x0, y0 + radius);
	plot(renderer, x0, y0 - radius);
	plot(renderer, x0 + radius, y0);
	plot(renderer, x0 - radius, y0);

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x + 1;

		plot(renderer, x0 + x, y0 + y);
		plot(renderer, x0 - x, y0 + y);
		plot(renderer, x0 + x, y0 - y);
		plot(renderer, x0 - x, y0 - y);
		plot(renderer, x0 + y, y0 + x);
		plot(renderer, x0 - y, y0 + x);
		plot(renderer, x0 + y, y0 - x);
		plot(renderer, x0 - y, y0 - x);
	}
}

void draw_board(board* b, SDL_Renderer* renderer, SDL_Rect* rect)
{
	int width = rect->w/3;
	int height = rect->h/3;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			SDL_Rect square;
			square.x = x * width + rect->x;
			square.y = y * height + rect->y;
			square.w = width;
			square.h = height;

			if (b->state[y][x] == CROSS)
			{
				draw_cross(renderer, square.x, square.y, square.w, square.h, 30);
			}
			else if (b->state[y][x] == NAUGHT)
			{
				draw_naught(renderer, square.x, square.y, square.w, square.h, 30);
			}


			SDL_RenderDrawRect(renderer, &square);
		}
	}
}

int get_move(SDL_Rect* rect, int screen_x, int screen_y, int* x, int* y)
{
	int width = rect->w / 3;
	int height = rect->h / 3;

	int pos_x = screen_x - rect->x;
	int pos_y = screen_y - rect->y;

	if (pos_x >= 0 && pos_x <= rect->w && pos_y >= 0 && pos_y <= rect->h)
	{
		*x = pos_x / width;
		*y = pos_y / height;
		return 1;
	}

	return 0;
}