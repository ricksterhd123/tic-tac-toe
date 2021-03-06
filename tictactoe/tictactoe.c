#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "board.h"
#include "gui.h"
#include "ai.h"

int main()
{
	int width = 640;
	int height = 480;
	struct board b;
	int game_over = 0;

	SDL_Window* window;
	SDL_Renderer* renderer;
	
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	
	window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	if (!window)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!renderer)
	{
		printf("Could not create renderer: %s\n", SDL_GetError());
		return 1;
	}

	start_game(&b);

	SDL_Rect square;
	square.w = 400;
	square.h = 400;
	square.x = (width / 2) - (square.w / 2);
	square.y = (height / 2) - (square.h / 2);

	piece computer = CROSS;
	piece human = NAUGHT;

	while (1)
	{
		piece current_piece = (b.moves % 2 == 0) ? CROSS : NAUGHT;
		piece winner;

		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				break;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN && !game_over && current_piece == computer)
			{
				int x, y;
				if (get_move(&square, e.button.x, e.button.y, &x, &y))
				{
					put_move(&b, x, y);
				}
			}
		}

		if (current_piece == human)
		{
			ai_get_move(&b, 10);
		}

		if (is_game_over(&b, &winner))
		{
			if (winner != EMPTY)
				printf("%s won!\n", (winner == NAUGHT) ? "Naughts" : "Crosses");
			else
				printf("Draw!\n");
			game_over = 1;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_board(&b, renderer, &square);
		SDL_RenderPresent(renderer);


		if (game_over)
		{
			SDL_Delay(3000);
			start_game(&b);
			game_over = 0;
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}