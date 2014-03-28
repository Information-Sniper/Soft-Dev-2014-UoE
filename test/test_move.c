#include <CUnit/CUnit.h>
#include "../defines.h"
#include "../board.h"
#include "../move.h"
#include "../move.c"

/* assuming rows = 6, cols = 7 */
void test_valid_move(void)
{
	board_t b;
	INT8    col;
	
	col = 3;
	b.heights[col] = 3;
	CU_ASSERT_TRUE(valid_move(&b, col));
	
	b.heights[col] = 6;
	CU_ASSERT_FALSE(valid_move(&b, col));
	
	col = 8;
	b.heights[col] = 3;
	CU_ASSERT_FALSE(valid_move(&b, col));  //
	
	col = -2;
	b.heights[col] = 3;
	CU_ASSERT_FALSE(valid_move(&b, col));  //
}

/* assuming rows = 6, cols = 7 */
void test_valid_moves_left(void)
{
	board_t b;
	
	/* no moves have been made yet */
	b.last_move = -1;
	CU_ASSERT_EQUAL(valid_moves_left(&b), 42);
	
	/* 10 moves have been made */
	b.last_move = 9;
	CU_ASSERT_EQUAL(valid_moves_left(&b), 32);
}


void test_make_move(void)
{
	board_t b;
	INT8    col;
	
	/* initialize board */
	board_init(&b);
	
	/* make 2 valid moves and assert board's members */
	
	col = 0;
	CU_ASSERT_EQUAL(make_move(&b, col), ERR_SUCCESS);
	CU_ASSERT_EQUAL(b.heights[col], 1);
	CU_ASSERT_EQUAL(b.last_move, 0);
	CU_ASSERT_EQUAL(b.moves[b.last_move], col);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_TWO);
	
	col = 6;
	CU_ASSERT_EQUAL(make_move(&b, col), ERR_SUCCESS);
	CU_ASSERT_EQUAL(b.heights[col], 1);
	CU_ASSERT_EQUAL(b.last_move, 1);
	CU_ASSERT_EQUAL(b.moves[b.last_move], col);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);

	/* make 2 invalid moves and assert board's members */
	/* they should be the same as the last valid move  */
	
	col = 7;
	CU_ASSERT_EQUAL(make_move(&b, col), ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(b.last_move, 1);
	CU_ASSERT_EQUAL(b.moves[b.last_move], 6);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);
	
	col = -4;
	CU_ASSERT_EQUAL(make_move(&b, col), ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(b.last_move, 1);
	CU_ASSERT_EQUAL(b.moves[b.last_move], 6);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);
}

void test_undo_move(void)
{
	board_t b;
	INT8    col;
	
	board_init(&b);
	
	/* make move in (5,0) */
	col = 5;
	b.grid[col][b.heights[col]] = PLAYER_ONE;
	b.heights[col]++;
	b.last_move++;
	b.moves[b.last_move] = col;
	b.cur_plr = -b.cur_plr;
	
	/* undo_move is valid */
	CU_ASSERT_EQUAL(undo_move(&b), ERR_SUCCESS);
	CU_ASSERT_EQUAL(b.last_move, -1);
	CU_ASSERT_EQUAL(b.heights[5], 0);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);
	
	/* undo_move is invalid - no more moves left */
	/* board struct members stay the same        */
	CU_ASSERT_EQUAL(undo_move(&b), ERR_NO_MOVES);
	CU_ASSERT_EQUAL(b.last_move, -1);
	CU_ASSERT_EQUAL(b.heights[5], 0);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);
	
}

void test_get_score(void)
{
	board_t b;
	POINT  *p;
	INT8   incr;
	
	board_init(&b);
	
	make_move(&b, 0); // O
	make_move(&b, 3); // X
	
	make_move(&b, 0); // O
	make_move(&b, 4); // X
	
	make_move(&b, 0); // O
	make_move(&b, 5); // X
	
	make_move(&b, 0); // O
	make_move(&b, 6); // X
	
	make_move(&b, 2); // O
	make_move(&b, 1); // X
	
	/* check the score from (0, 0) to (0, 4) - vertical */
	p = &(b.grid[0][0]);
	CU_ASSERT_EQUAL(get_score(p, 1), 4);
	
	p = &(b.grid[0][1]);
	CU_ASSERT_EQUAL(get_score(p, 1), 3);
	
	p = &(b.grid[0][2]);
	CU_ASSERT_EQUAL(get_score(p, 1), 2);
/*	
	p = &(b.grid[0][3]);
	CU_ASSERT_EQUAL(get_score(p, 1), 1);
	
	p = &(b.grid[0][4]);
	CU_ASSERT_EQUAL(get_score(p, 1), 0);
*/
	
	/* check the score from (3, 0) to (6, 0) - horizontal */
	p = &(b.grid[3][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), -4);
/*	
	p = &(b.grid[4][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), -3);
	
	p = &(b.grid[5][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), -2);
	
	p = &(b.grid[6][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), -1);
*/	
	/* check score on (1, 0) and (2, 0) - horizontal */
	p = &(b.grid[1][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), 0);
	
	p = &(b.grid[2][0]);
	CU_ASSERT_EQUAL(get_score(p, ROWS), 0);
}

void test_get_strength(void)
{
	board_t b;
	
	board_init(&b);
	
	make_move(&b, 0); // O (0,0)
	make_move(&b, 2); // X (2,0)
	make_move(&b, 0); // O (0,1)
	make_move(&b, 3); // X (3,0)
	make_move(&b, 0); // O (0,2)
	make_move(&b, 0); // X (0,3)
	make_move(&b, 1); // O (1,0)
	make_move(&b, 5); // X (5,0)
	make_move(&b, 4); // O (4,0)
	make_move(&b, 4); // X (4,1)
	make_move(&b, 3); // O (3,1)
	make_move(&b, 3); // X (3,2)
	make_move(&b, 1); // O (1,1)
	make_move(&b, 2); // X (2,1)
	make_move(&b, 2); // O (2,2)
	make_move(&b, 3); // X (3,3)
	
	CU_ASSERT_EQUAL(get_strength(&b), -70);
}









/*



// don't change this unless you understand it
static int min_value(board_t *b, INT8 ply)
{
	int moves[COLS];
	int lowest = 0;
	int i;
	
	for (i = 0; i < COLS; i++)
	{
		moves[i] = INT_MAX;
		
		if (valid_move(b, i))
		{
			make_move(b, i);
			
			if ((winner_is(b) == NONE) && ply > 0)
			{
				moves[i] = min_value(b, ply - 1);
			}
			else 
			{
				moves[i] = -get_strength(b);
			}
			
			if (moves[i] < moves[lowest])
			{
				lowest = i;
			}
			undo_move(b);
		}
	}
	return moves[lowest];
}

int get_reasoned_move(board_t *b)
{
	int moves[COLS];
	int highest = 0;
	int i;
	
	for(i = 0; i < COLS; i++)
	{
		moves[i] = INT_MIN;
		
		if (valid_move(b, i))
		{
			make_move(b, i);
			moves[i] = min_value(b, 4);  // check this shit

			if (moves[i] >= moves[highest])
			{
				highest = i;
			}
			undo_move(b);
		} 
	}
	return highest;
}
*/

