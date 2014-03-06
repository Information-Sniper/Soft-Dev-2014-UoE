#include <limits.h>
#include "defines.h"
#include "board.h"
#include "move.h"

int valid_move(board_t *b, int column)
{
	return b->heights[column] < b->rows;
}

int valid_moves_left(board_t *b)
{
	return b->lm < ((b->cols * b->rows) -1);
}

void make_move(board_t *b, int column)
{
	set_state(b->grid[column][b->heights[column]], b->current_player);

	b->heights[column]++;
	b->lm++;
	b->moves[b->lm] = column;
	b->current_player = -b->current_player;
}

void undo_move(board_t *b)
{
	set_state(b->grid[b->moves[b->lm]][b->heights[b->moves[b->lm]] - 1], EMPTY);
	b->heights[b->moves[b->lm]]--;
	b->lm--;
	b->current_player = -b->current_player;
}

int get_random_player_move(board_t *b)
{
	int val = -1;
	int possible[COLS];
	int i;
	
	for (i = 0; i < COLS; i++)
	{
		if (valid_move(b, i))
		{
			possible[i] = 1;
		}
		else
		{
			possible[i] = 0;
		}
	}

	while (val == -1)
	{
		int rad = rand() % COLS;
		
		if (possible[rad] == 1)
		{
			val = rad;
		}
	}
	return val;
}

// should return a number
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
			moves[i] = min_value(b, ROWS - 2);
			
			if (moves[i] >= moves[highest])
			{
				highest = i;
			}
			undo_move(b);
		} 
	}
	return highest;
}

int get_strength(board_t *b)
{
	int sum = 0;
	int weights[] = {0, 1, 10, 50, 600};
	int i;
	
	for (i = 0; i < POS_COMBOS; i++)
	{
		sum += weights[abs(get_score(b->cl[i]))];
	}
	
	return sum + 16;
}

// don't change this unless you understand it
int min_value(board_t *b, int ply)
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
				moves[i] = get_strength(b);
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