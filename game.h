#ifndef GAME_H
#define GAME_H

#include "defines.h"
#include "board.h"

/* public functions */

/* Returns winner player, or NONE */
INT8 winner_is         (const board_t *b);
INT8 get_current_player(const board_t *b);
INT8 get_last_player   (const board_t *b);

/*
 * If return value is ERR_SUCCESS, "input" is 
 * guaranteed to be a positive integer up to
 * 127. Else, its value is undefined.
 */
int get_user_input(INT8 *input);

/* private function */

/*
 * Helper function
 *
 * Input:
 *    b:           pointer to an initialized board_t struct
 *    direction:   the direction in which to search
 * Output:
 *    combos:      The number of possible combinations for
 *                 given direction.
 *    point:       the first point in a line of 4.
 *    ptr_incr:    if we add this to "point" we get the
 *                 next point in that combination
 */

static int get_window  (      INT8     *combos,
                              POINT   **point,
						      INT8     *ptr_incr,
			            const board_t  *b,
						      int       direction);
							  
#endif /* GAME_H */
