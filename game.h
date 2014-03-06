#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "board.h"

int   get_score(point_t *points[]);
int   winner_is(board_t *b);
int   get_current_player(board_t *b);
char *to_string(board_t *b);

#endif // GAME_H

