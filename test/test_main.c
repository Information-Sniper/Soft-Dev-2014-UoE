#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "connect4.h"

/* Run test suite */
int main(void)
{
    CU_pSuite ps_board = NULL;
    CU_pSuite ps_game  = NULL;
    CU_pSuite ps_move  = NULL;

    /* initialise CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
	{
        return CU_get_error();
	}

	/* Add suites */
    if(!(ps_board = CU_add_suite("board.h tests", NULL, NULL)))
	{
        CU_cleanup_registry();
        return CU_get_error();
    }

	if(!(ps_game = CU_add_suite("game.h tests", NULL, NULL)))
	{
        CU_cleanup_registry();
        return CU_get_error();
    }
	
	if(!(ps_move = CU_add_suite("move.h tests", NULL, NULL)))
	{
        CU_cleanup_registry();
        return CU_get_error();
    }
	
    /* Add tests to the ps_board suite */
    CU_add_test(ps_board, "test_board_init",      test_board_init);
    CU_add_test(ps_board, "test_board_set_point", test_board_set_point);
    CU_add_test(ps_board, "test_board_get_point", test_board_get_point);


	/* Add tests to the ps_game suite */
    CU_add_test(ps_game, "test_winner_is",          test_winner_is);
    CU_add_test(ps_game, "test_get_current_player", test_get_current_player);
    CU_add_test(ps_game, "test_get_last_player",    test_get_last_player);
    CU_add_test(ps_game, "test_get_user_input",     test_get_user_input);
    CU_add_test(ps_game, "test_get_window",         test_get_window);
	
	/* Add tests to the ps_move suite */
    CU_add_test(ps_move, "test_valid_move",        test_valid_move);
    CU_add_test(ps_move, "test_valid_moves_left",  test_valid_moves_left);
    CU_add_test(ps_move, "test_make_move",         test_make_move);
    CU_add_test(ps_move, "test_undo_move",         test_undo_move);
    CU_add_test(ps_move, "test_get_score",         test_get_score);
    CU_add_test(ps_move, "test_get_strength",      test_get_strength);
	
    /* Set the basic run mode and run all suites */
    CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_suite(ps_board);
	CU_basic_run_suite(ps_game);
	CU_basic_run_suite(ps_move);
    
    /* Cleanup and exit */
	CU_cleanup_registry();
    return CU_get_error();
}
