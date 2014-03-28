#include <CUnit/CUnit.h>
#include "defines.h"
#include "board.h"
#include "game.h"

void test_get_user_input(void)
{
	CU_FAIL("Not implemented yet");
}

void test_get_current_player(void)
{
	board_t b;
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(get_current_player(&b), PLAYER_ONE);
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(get_current_player(&b), PLAYER_TWO);
	
	b.cur_plr = NONE;
	CU_ASSERT_EQUAL(get_current_player(&b), NONE);
}

void test_get_last_player(void)
{
	board_t b;
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(get_last_player(&b), PLAYER_TWO);
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(get_last_player(&b), PLAYER_ONE);
	
	b.cur_plr = NONE;
	CU_ASSERT_EQUAL(get_last_player(&b), NONE);
}

void test_get_window(void)
{
	board_t b;
	INT8    combos;
	POINT  *p;
	INT8    ptr_incr;
	int     dir;
	
	b.last_move = 0;
	
	/* We assume that the board is (7, 6) = 6 rows, 7 columns */

	/*(x, y) = (0, 0)*/
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 1;
	
	/* Check direction and ptr_incr */
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	CU_ASSERT_EQUAL(ptr_incr, ROWS);
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	CU_ASSERT_EQUAL(ptr_incr, 1);
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	CU_ASSERT_EQUAL(ptr_incr, ROWS + 1);
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	CU_ASSERT_EQUAL(ptr_incr, ROWS - 1);
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b,  5), ERR_INVALID_INPUT);
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, -3), ERR_INVALID_INPUT);
	
	
	/*(x, y) = (6, 0)*/
	b.moves[b.last_move] = 6;
	b.heights[b.moves[b.last_move]] = 1;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[6][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[6][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][3]));
	
	/*(x, y) = (0, 5)*/
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 6;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][5]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][5]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][5]));
	
	
	/*(x, y) = (6, 5)*/
	b.moves[b.last_move] = 6;
	b.heights[b.moves[b.last_move]] = 6;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][5]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[6][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[6][5]));
	
	
	/*(x, y) = (3, 0)*/
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 1;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 4);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][3]));
	
	
	/*(x, y) = (3, 5)*/
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 6;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 4);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][5]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][5]));
	
	
	/*(x, y) = (0, 2)*/
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 3;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 3);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	
	/*(x, y) = (6, 2)*/
	b.moves[b.last_move] = 6;
	b.heights[b.moves[b.last_move]] = 3;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 3);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[6][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 0);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[4][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 1);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][5]));
	
	
	/*(x, y) = (3, 2)*/
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 3;
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, HORIZONTAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 4);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][2]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, VERTICAL), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 3);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[3][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, DOWNLEFT_UPRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 3);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[1][0]));
	
	CU_ASSERT_EQUAL(get_window(&combos, &p, &ptr_incr, &b, UPLEFT_DOWNRIGHT), ERR_SUCCESS);
	CU_ASSERT_EQUAL(combos, 3);
	CU_ASSERT_PTR_EQUAL(p, &(b.grid[0][5]));
}

void test_winner_is(void)
{
	board_t b;
	INT8   x, y;

	/* We assume that the board is (7, 6) = 6 rows, 7 columns */
	
	/* horizontal line of 4: from (0, 0) to (3, 0) */
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 1;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 2;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), PLAYER_ONE);
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	
	/* vertical line of 4: from (0, 0) to (0, 3) */
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 2;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 3;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 4;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), PLAYER_TWO);
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	/* downleft_upright line of 4: from (0, 0) to (3, 3) */
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 1;
	b.heights[b.moves[b.last_move]] = 2;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 2;
	b.heights[b.moves[b.last_move]] = 3;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 4;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), PLAYER_TWO);
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	/* upleft_downright line of 4: from (3, 3) to (6, 0) */
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 4;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 4;
	b.heights[b.moves[b.last_move]] = 3;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 5;
	b.heights[b.moves[b.last_move]] = 2;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 6;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), PLAYER_ONE);
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	/* horizontal line of 7: from (0, 0) to (6, 0) - no winner*/
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 0;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 1;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 2;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 4;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 5;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.last_move++;
	b.moves[b.last_move] = 6;
	b.heights[b.moves[b.last_move]] = 1;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_ONE;
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	/* vertical line of 5 with gap: from (3, 1) to (3, 5) - no winner*/
	board_init(&b);
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 2;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 3;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 4;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = NONE;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 5;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.last_move++;
	b.moves[b.last_move] = 3;
	b.heights[b.moves[b.last_move]] = 6;
	x = b.moves[b.last_move];
	y = b.heights[b.moves[b.last_move]] - 1;
	b.grid[x][y] = PLAYER_TWO;
	
	b.cur_plr = PLAYER_ONE;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
	
	b.cur_plr = PLAYER_TWO;
	CU_ASSERT_EQUAL(winner_is(&b), NONE);
}


