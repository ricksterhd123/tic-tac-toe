#include "ai.h"

/// <summary>
/// Generates list of children for node
/// </summary>
/// <param name="node"></param>
/// <param name="child"></param>
void get_moves(board* node, board* child, int no_children)
{
	int i = 0;
	
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (node->state[y][x] == EMPTY)
			{
				put_move(child + i++, x, y);
			}
		}
	}
}

/// <summary>
/// Count the heuristic for row y
/// </summary>
/// <param name="b"></param>
/// <param name="p"></param>
/// <param name="y"></param>
/// <returns></returns>
float count_row(board* b, piece p, int y)
{
	float count = 0;

	//// singles
	//for (int x = 0; x < WIDTH; x++)
	//	if (b->state[y][x] == p)
	//		count++;

	// doubles
	for (int x = 0; x < WIDTH - 1; x++)
		if (b->state[y][x] == p && b->state[y][x + 1] == p)
			count += 4;
	
	// triples
	if (b->state[y][0] == p && b->state[y][1] == p && b->state[y][2] == p)
		count += 16;

	return count;
}

/// <summary>
/// Count the heuristic for column x
/// </summary>
/// <param name="b"></param>
/// <param name="p"></param>
/// <param name="x"></param>
/// <returns></returns>
float count_col(board* b, piece p, int x)
{
	float count = 0;

	//// singles
	//for (int y = 0; y < HEIGHT; y++)
	//	if (b->state[y][x] == p)
	//		count++;

	// doubles
	for (int y = 0; y < HEIGHT - 1; y++)
		if (b->state[y][x] == p && b->state[y + 1][x] == p)
			count += 4;

	// triples
	if (b->state[0][x] == p && b->state[1][x] == p && b->state[2][x] == p)
		count += 16;

	return count;
}

/// <summary>
/// Count the heuristic for both diagonals
/// </summary>
/// <param name="b"></param>
/// <param name="p"></param>
/// <returns></returns>
float count_diag(board* b, piece p)
{
	float count = 0;
	int diagL[3][2] = { {0, 0}, {1, 1}, {2, 2} };
	int diagR[3][2] = { {0, 2}, {1, 1}, {2, 0} };

	//// diagL singles
	//for (int i = 0; i < 3; i++)
	//{
	//	int x = diagL[i][0];
	//	int y = diagL[i][1];
	//	
	//	if (b->state[y][x] == p)
	//		count++;
	//}

	//// diagR singles
	//for (int i = 0; i < 3; i++)
	//{
	//	int x = diagR[i][0];
	//	int y = diagR[i][1];

	//	if (b->state[y][x] == p)
	//		count++;
	//}

	// diagL doubles
	for (int i = 0; i < 2; i++)
	{
		int x1 = diagL[i][0];
		int y1 = diagL[i][1];
		int x2 = diagL[i + 1][0];
		int y2 = diagL[i + 1][1];

		if (b->state[y1][x1] == p && b->state[y2][x2] == p)
			count += 4;
	}

	// diagR doubles
	for (int i = 0; i < 2; i++)
	{
		int x1 = diagR[i][0];
		int y1 = diagR[i][1];
		int x2 = diagR[i + 1][0];
		int y2 = diagR[i + 1][1];

		if (b->state[y1][x1] == p && b->state[y2][x2] == p)
			count += 4;
	}

	// diagL triples
	if (b->state[0][0] == p && b->state[1][1] == p && b->state[2][2] == p)
		count += 16;

	// diagR triples
	if (b->state[0][2] == p && b->state[1][1] == p && b->state[2][0] == p)
		count += 16;
	
	return count;
}

/// <summary>
/// Calculate the heuristic of the board state using the piece of the last move
/// </summary>
/// <param name="b">The board state to calculate the heuristic</param>
/// <returns></returns>
float heuristic(board* b)
{
	//float value = 0;

	//// Use the piece of the last move
	piece p = ((b->moves) % 2 == 0) ? CROSS : NAUGHT;

	//// Rows
	//for (int y = 0; y < HEIGHT; y++)
	//	value += count_row(b, p, y);

	//// Columns
	//for (int x = 0; x < WIDTH; x++)
	//	value += count_col(b, p, x);

	//// Diagonals
	//value += count_diag(b, p);

	piece* winner;

	if (is_game_over(b, &winner))
		return 1;
	else
		return 0;
}

/// <summary>
/// minimax of the board state limited by depth
/// </summary>
/// <param name="node">Board state to calculate minimax</param>
/// <param name="depth">Max depth</param>
/// <param name="max">Max piece</param>
/// <returns></returns>
float minimax(board* node, int depth, piece maximizer)
{
	if (node->moves == 9)
		return heuristic(node);

	float value = 0;
	int no_children = 9 - node->moves;
	board* child = malloc(sizeof(board) * no_children);

	// Error handling needs to be thought about in the future...
	assert(child != NULL);

	// Copy node into each child
	for (int i = 0; i < no_children; i++)
	{
		empty_board(&child[i]);
		cpy_board(node, &child[i]);
	}

	// Generate each possible next move
	get_moves(node, child, no_children);

	// This might cause a bug - we should double check that we mean current piece or piece of the last move...
	piece current_piece = (node->moves % 2 == 0) ? CROSS : NAUGHT;

	// Are we the maximizing player?
	if (maximizer == current_piece)
	{
		value = -INFINITY;
		for (int i = 0; i < no_children; i++)
		{
			value = fmaxf(value, minimax(&child[i], depth - 1, maximizer));
		}
	}
	else
	{
		value = INFINITY;
		for (int i = 0; i < no_children; i++)
		{
			value = fminf(value, minimax(&child[i], depth - 1, maximizer));
		}
	}

	free(child);
	return value;
}

/// <summary>
/// Get the next move from the A.I and put it on the board.
/// </summary>
/// <param name="b"></param>
/// <param name="max_depth"></param>
void ai_get_move(board* b, int max_depth)
{
	// Get the current turn
	piece p = (b->moves % 2 == 0) ? CROSS : NAUGHT;

	int no_children = 9 - b->moves;
	board* child = malloc(sizeof(board) * no_children);

	// Error handling needs to be thought about in the future...
	assert(child != NULL);

	// Copy node into each child
	for (int i = 0; i < no_children; i++)
	{

		empty_board(&child[i]);
		cpy_board(b, &child[i]);
	}

	// Generate each possible next move
	get_moves(b, child, no_children);

	float value = -INFINITY;
	board best = *b;

	for (int i = 0; i < no_children; i++)
	{
		float temp = minimax(&child[i], max_depth, p);
		if (temp > value)
		{
			value = temp;
			best = child[i];
		}
	}

	// Unsafe
	//memcpy(b, &best, sizeof(best));
	*b = best;
	free(child);
}