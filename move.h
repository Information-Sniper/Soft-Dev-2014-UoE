#ifndef MOVE_H
#define MOVE_H

#include "board.h"

int  valid_move(board_t *b, int column);
int  valid_moves_left(board_t *b);
void make_move(board_t *b, int column);
void undo_move(board_t *b);
int  get_random_player_move(board_t *b);
int  get_reasoned_move(board_t *b);
int  get_strength(board_t *b);
int  min_value(board_t *b, int ply);
int  max_value(board_t *b, int ply);

/* ply = ?? */

#endif // MOVE_H
