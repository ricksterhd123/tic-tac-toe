#pragma once
#include "board.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void get_moves(board* node, board* child, int no_children);
float count_row(board* b, piece p, int y);
float count_col(board* b, piece p, int x);
float count_diag(board* b, piece p);
float heuristic(board* b);
float minimax(board* node, int depth, piece maximizer);
void ai_get_move(board* b, int max_depth);