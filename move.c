#include <limits.h>
#include "defines.h"
#include "board.h"
#include "game.h"
#include "move.h"

INT8 valid_move(const board_t *b, INT8 col)
{
	if (col < 0 || col >= COLS)
	{
		return 0;
	}
	else
	{
		return b->heights[col] < ROWS;
	}
}

short valid_moves_left(const board_t *b)
{
	return (ROWS * COLS - 1) - b->last_move;
}

int make_move(board_t *b, INT8 col)
{
	int error = board_set_point(b, col, b->heights[col], b->cur_plr);

	if (error == ERR_SUCCESS)
	{
		b->heights[col]++;
		b->last_move++;
		b->moves[b->last_move] = col;
		b->cur_plr = -b->cur_plr;
	}

	return error;
}

INT8 get_reasoned_move(board_t *b)
{
	int  moves[COLS];
	INT8 highest = 0;
	INT8 i;
	
	for(i = 0; i < COLS; i++)
	{
		moves[i] = INT_MIN;
		
		if (valid_move(b, i))
		{
			make_move(b, i);
			moves[i] = min_value(b, DIFFICULTY);

			if (moves[i] >= moves[highest])
			{
				highest = i;
			}
			undo_move(b);
		} 
	}
	return highest;
}

static int undo_move(board_t *b)
{
	INT8 x;
	INT8 y;
	int  error;
	
	if (b->last_move >= 0)
	{
		x = b->moves[b->last_move];
		y = b->heights[x] - 1;
		error = board_set_point(b, x, y, NONE);
		
		if (error == ERR_SUCCESS)
		{
			b->heights[x]--;
			b->last_move--;
			b->cur_plr = -b->cur_plr;
		}
	}
	else
	{
		error = ERR_NO_MOVES;
	}

	return error;
}

/*
 * OUT:   score
 *  IN:  *p
 *  IN:   increment
 *
 *  score: The score of the current line of 4.
 *         All tokens of the line have to belong
 *         to the same player, else the score is 0.
 *         The sign of the score depends on the
 *         player; positive for PLAYER_ONE,
 *                 negative for PLAYER_TWO
 *
 * *p: pointer to the first token in the line of 4.
 *     The first token is considered to be the
 *     leftmost token for the 
 *         HORIZONTAL,
 *         DOWNLEFT_UPRIGHT and
 *         UPLEFT_DOWNRIGHT directions
 *     and the bottom token for the
 *         VERTICAL direction.
 * 
 *  increment: the value that has to be added
 *             to *p to get to the next token
 *             in the line.
 */

/* 
 * It is the programmers job to ensure that the 
 * pointer to point (*p) is the 1st in a line of 4
 * for the direction implied by the increment.
 * If a line of 4 is not possible from that position,
 * get_score() will return an invalid result.
 */
 
static INT8 get_score(POINT *p, INT8 increment)
{
	char  player_1 = 0;
	char  player_2 = 0;
	char  i;

	for (i = 0; i < FOUR; i++)
	{
		if (*p == PLAYER_ONE)
		{
			player_1++;
		}
		else if (*p == PLAYER_TWO)
		{
			player_2--;
		}
		
		p += increment;
	}
	
	if (player_1 > 0 && player_2 == 0)
	{
		return player_1;
	}
	else if (player_2 < 0 && player_1 == 0)
	{
		return player_2;
	}
	else
	{
		return 0;
	}
}


/*
 * OUT:   sum
 *  IN:  *b
 *
 * sum: An integer that is the sum of the scores
 *      of all possible winning combinations in
 *      the board. If positive, PLAYER_ONE has 
 *      an advantage over PLAYER_TWO. If negative,
 *      the opposite. If zero, there is no
 *      advantage.
 *
 *  *b: pointer to an initialized board structure
 */

static int get_strength(const board_t *b)
{
	short  weights[] = {0, 1, 10, 50, 600};
	INT8   score;
	int    sum = 0;
	int    dir;
	INT8   incr;
	INT8   x, x_from, x_to;
	INT8   y, y_from, y_to;
	POINT *point;

	for (dir = HORIZONTAL; dir < DIRECTIONS; dir++)
	{
		x_from = 0;
		y_from = 0;
		
		switch (dir)
		{
		case HORIZONTAL:
			x_to = COLS - FOUR + 1;
			y_to = Y_DIM;
			incr = Y_DIM;
			break;
		case VERTICAL:
			x_to = COLS;
			y_to = Y_DIM - FOUR + 1;
			incr = 1;
			break;
		case DOWNLEFT_UPRIGHT:
			x_to = COLS - FOUR + 1;
			y_to = Y_DIM - FOUR + 1;
			incr = Y_DIM + 1;
			break;
		case UPLEFT_DOWNRIGHT:
			y_from = FOUR - 1;
			x_to = COLS - FOUR + 1;
			y_to = Y_DIM;
			incr = Y_DIM - 1;
			break;
		}

		for (x = x_from; x < x_to; x++)
		{
			for (y = y_from; y < y_to; y++)
			{
				point = &(b->grid[x][y]);
			
				score = get_score(point, incr);
				sum += (score >= 0) ? weights[score] : -weights[-score];
			}
		}
	}
	
	sum += (get_current_player(b) == PLAYER_ONE) ? 16 : -16;
	
	return sum;
}

static int min_value(board_t *b, INT8 ply)
{
	int  moves[COLS];
	int  lowest = 0;
	INT8 i;
	
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
