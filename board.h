#ifndef BOARD_H
#define BOARD_H

#include "point.h"

typedef struct board
{
	point_t ***grid;
	int *heights;

	int cols;
	int rows;

	int *moves;
	int lm;

	int cp;
	point_t ***cl;
} board_t;

board_t   *createBoard(int a, int b);
void       deleteboard(board_t *p);
point_t ***generateCL(point_t ***grid);

#endif // BOARD_H
