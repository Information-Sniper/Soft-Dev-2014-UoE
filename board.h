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

	int current_player;
	point_t ***cl;
} board_t;

board_t   *create_board(int x, int y);
void       delete_board(board_t *b);
point_t ***generate_CL(point_t ***grid);


/* cl = connect line ?? */


#endif // BOARD_H
