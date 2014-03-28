#ifndef MOVE_H
#define MOVE_H

#include "defines.h"
#include "board.h"

/* public functions */
INT8   valid_move       (const board_t *b, INT8 col);
short  valid_moves_left (const board_t *b);
int    make_move        (board_t *b, INT8 col);
int    get_reasoned_move(board_t *b);

/* private functions */
static int  undo_move   (board_t *b);
static INT8 get_score   (POINT *p, INT8 increment);
static int  get_strength(const board_t *b);
static int  min_value   (board_t *b, INT8 ply);

#ifdef UNIT_TEST
void test_valid_move      (void);
void test_valid_moves_left(void);
void test_make_move       (void);
void test_undo_move       (void);
void test_get_score       (void);
void test_get_strength    (void);
#endif /* UNIT_TEST */

#endif // MOVE_H
