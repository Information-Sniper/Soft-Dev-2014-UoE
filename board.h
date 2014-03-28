#ifndef BOARD_H
#define BOARD_H

/*
 * board_t: represents the game board
 *
 * grid:		2D array of size [X_DIM][Y_DIM]. It's the actual game board.
 * moves:		1D array of length [X_DIM * Y_DIM]. 
 *				ith cell keeps the column played on the ith move
 * heights:		1D array of length [X_DIM]. Keeps the height of each column
 * cur_plr:		keeps track of the current player
 * last_move:	keeps last move's number.
 */

typedef struct board
{
	POINT grid[X_DIM][Y_DIM];
	INT8  moves[X_DIM * Y_DIM];
	INT8  heights[X_DIM];
	INT8  cur_plr;
	short last_move;
} board_t;

/* Initializes the board */
void board_init((board_t *b);

/* Prints the curent state of the board */
void board_display(const board_t *b);

/* Sets point (x,y) to "player". Returns error value */
int board_set_point(board_t *b, INT8 x, INT8 y, INT8 player);

/* Outputs point (x,y)'s state to "p". Returns error value */
int board_get_point(POINT *p, const board_t *b, INT8 x, INT8 y);

#ifdef UNIT_TEST
void test_board_init     (void);
void test_board_display  (void);
void test_board_set_point(void);
void test_board_get_point(void);
#endif /* UNIT_TEST */

#endif // BOARD_H
