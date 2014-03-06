#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "board.h"

int   getScore(point_t *points[]);
int   winnerIs(board_t *b);
int   cp(board_t *b);
char *toString(board_t *b);

#endif // GAME_H

