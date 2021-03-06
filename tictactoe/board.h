#pragma once
#define WIDTH 3
#define HEIGHT 3

enum board_piece
{
	EMPTY,
	NAUGHT,
	CROSS
};
typedef enum board_piece piece;

struct board
{
	int moves;
	piece state[WIDTH][HEIGHT];
};
typedef struct board board;

void empty_board(board* b);
piece get_winner(board* b);
int is_game_over(board* b, piece* winner);
int put_move(board* b, int x, int y);
void cpy_board(board* src, board* dest);
void start_game(board* b);
