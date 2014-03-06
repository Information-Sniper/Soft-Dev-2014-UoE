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
	set_state(b->grid[b->moves[b->lm]][b->heights[b->moves[b->lm]] - 1], (EMPTY));
	b->heights[b->moves[b->lm]]--;
	b->lm--;
	b->current_player = -b->current_player;
}

int get_random_player_move(board_t *b)
{
	int val = -1;
	int possible[7];
	int i;
	
	for (i = 0; i < 7; i++)
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
		int rad = rand() % 7;
		
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
	int moves[7];
	int highest = 0;
	int i;
	
	for(i = 0; i < 7; i++)
	{
		moves[i] = INT_MIN;
		
		if (valid_move(b, i))
		{
			make_move(b, i);
			moves[i] = min_value(b, 4);
			
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
	
	for (i = 0; i < 69; i++)
	{
		sum += (get_score(b->cl[i]) > 0) ? weights[abs(get_score(b->cl[i]))] : -weights[abs(get_score(b->cl[i]))];
	}
	return sum + (b->current_player == PLAYER_ONE ? 16 : -16);
}

// don't change this unless you understand it
int min_value(board_t *b, int ply)
{
	int moves[7];
	int lowest = 0;
	int i;
	
	for (i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		
		if (valid_move(b, i))
		{
			make_move(b, i);
			
			if ((winner_is(b) == 0) && ply > 0)
			{
				moves[i] = max_value(b, ply - 1);
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

//careful with this
int max_value(board_t *b, int ply)
{
	int moves[7];
	int highest = 0;
	int i;
	
	for (i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		if (valid_move(b, i))
		{
			make_move(b, i);

			if ((winner_is(b) == 0) && ply > 0)
			{
				moves[i] = min_value(b, ply - 1);
			}
			else
			{
				moves[i] = -get_strength(b);
			}

			if (moves[i] < moves[highest])
			{
				highest = i;
			}
			
			undo_move(b);
		}
	}
	return moves[highest];
}
