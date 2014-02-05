#ifndef MOVE_H
#define MOVE_H

#include "board.h"

int  validMove(board_t *b, int column);
int  validMovesLeft(board_t *b);
void makeMove(board_t *b, int column);
void undoMove(board_t *b);
int  getRandomPlayerMove(board_t *b);
int  getReasonedMove(board_t *cB);
int  getStrength(board_t *b);
int  minValue(board_t *cB, int ply);
int  maxValue(board_t *cB, int ply);

#endif // MOVE_H
