#include <CUnit/CUnit.h>
#include "defines.h"
#include "board.h"

void test_board_init(void)
{
	board_t b;
	INT8 x, y;

	board_init(&b);
	
	CU_ASSERT_EQUAL(b.last_move, -1);
	CU_ASSERT_EQUAL(b.cur_plr, PLAYER_ONE);
	
	for (x = 0; x < X_DIM; x++)
	{
		for (y = 0; y < Y_DIM; y++)
		{
			CU_ASSERT_EQUAL(b.grid[x][y], NONE);
		}
		CU_ASSERT_EQUAL(b.heights[x], 0);
	}
}


void test_board_display(void)
{
	CU_PASS("Cannot create test for board_display()\n");
}


void test_board_set_point(void)
{
	board_t b;

	CU_ASSERT_EQUAL(board_set_point(&b, 0, 0, PLAYER_ONE), ERR_SUCCESS);
	CU_ASSERT_EQUAL(board_set_point(&b, 0, 0, PLAYER_TWO), ERR_SUCCESS);
	CU_ASSERT_EQUAL(board_set_point(&b, 0, 0, NONE),       ERR_SUCCESS);
	
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM - 1, 0, PLAYER_ONE),   ERR_SUCCESS);
	CU_ASSERT_EQUAL(board_set_point(&b, 0, Y_DIM - 1, PLAYER_TWO),   ERR_SUCCESS);
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM - 1, Y_DIM - 1, NONE), ERR_SUCCESS);
	
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM, 0, PLAYER_ONE),     ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_set_point(&b, 0, Y_DIM, PLAYER_ONE),     ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM, Y_DIM, PLAYER_ONE), ERR_OUT_OF_BOUNDS);
	
	CU_ASSERT_EQUAL(board_set_point(&b, -1, 0, PLAYER_ONE),  ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_set_point(&b, 0, -1, PLAYER_ONE),  ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_set_point(&b, -1, -1, PLAYER_ONE), ERR_OUT_OF_BOUNDS);
	
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM / 2, Y_DIM / 3, 5),  ERR_INVALID_INPUT);
	CU_ASSERT_EQUAL(board_set_point(&b, X_DIM / 2, Y_DIM / 3, -8), ERR_INVALID_INPUT);
}


void test_board_get_point(void)
{
	board_t b;
	POINT   p;

	b.grid[0][0] = NONE;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, 0, 0), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, NONE);

	b.grid[0][0] = PLAYER_ONE;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, 0, 0), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, PLAYER_ONE);
	
	b.grid[0][0] = PLAYER_TWO;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, 0, 0), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, PLAYER_TWO);
	
	
	b.grid[X_DIM - 1][0] = NONE;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, X_DIM - 1, 0), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, NONE);
	
	b.grid[0][Y_DIM - 1] = PLAYER_ONE;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, 0, Y_DIM - 1), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, PLAYER_ONE);
	
	
	b.grid[X_DIM - 1][Y_DIM - 1] = PLAYER_TWO;
	CU_ASSERT_EQUAL(board_get_point(&p, &b, X_DIM - 1, Y_DIM - 1), ERR_SUCCESS);
	CU_ASSERT_EQUAL(p, PLAYER_TWO);

	CU_ASSERT_EQUAL(board_get_point(&p, &b, X_DIM, 0),     ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_get_point(&p, &b, 0, Y_DIM),     ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_get_point(&p, &b, X_DIM, Y_DIM), ERR_OUT_OF_BOUNDS);
	
	CU_ASSERT_EQUAL(board_get_point(&p, &b, -1,  0), ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_get_point(&p, &b,  0, -1), ERR_OUT_OF_BOUNDS);
	CU_ASSERT_EQUAL(board_get_point(&p, &b, -1, -1), ERR_OUT_OF_BOUNDS);
}