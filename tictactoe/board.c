#include "board.h"

void empty_board(board* b)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			b->state[y][x] = EMPTY;
}

piece get_winner(board* b)
{
	// horizontal
	for (int y = 0; y < HEIGHT; y++)
		if (b->state[y][0] != EMPTY && b->state[y][0] == b->state[y][1] && b->state[y][1] == b->state[y][2] && b->state[y][0] == b->state[y][2])
			return b->state[y][0];

	// vertical
	for (int x = 0; x < WIDTH; x++)
		if (b->state[0][x] != EMPTY && b->state[0][x] == b->state[1][x] && b->state[1][x] == b->state[2][x] && b->state[0][x] == b->state[2][x])
			return b->state[0][x];

	// diagonal left to right
	if (b->state[0][0] != EMPTY && b->state[0][0] == b->state[1][1] && b->state[1][1] == b->state[2][2] && b->state[0][0] == b->state[2][2])
		return b->state[0][0];

	// diagonal right to left
	if (b->state[0][2] != EMPTY && b->state[0][2] == b->state[1][1] && b->state[1][1] == b->state[2][0] && b->state[0][2] == b->state[2][0])
		return b->state[0][2];

	// otherwise
	return EMPTY;
}

int is_game_over(board* b, piece* winner)
{
	piece winning = get_winner(b);
	if (b->moves == 9 || winning != EMPTY)
	{
		*winner = winning;
		return 1;
	}
	return 0;
}

int put_move(board* b, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && b->state[y][x] == EMPTY)
	{
		b->state[y][x] = (b->moves++ % 2 == 0) ? CROSS : NAUGHT;
		return 1;
	}
	
	return 0;
}

void start_game(board* b)
{
	empty_board(b);
	b->moves = 0;
}