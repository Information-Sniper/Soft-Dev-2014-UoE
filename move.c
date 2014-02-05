#include <limits.h>
#include "defines.h"
#include "board.h"
#include "move.h"

int validMove(board_t *b, int column)
{
	return b->heights[column] < b->rows;
}

int validMovesLeft(board_t *b)
{
	return b->lm < ((b->cols * b->rows) -1);
}

void makeMove(board_t *b, int column)
{
	setState(b->grid[column][b->heights[column]], b->cp);

	b->heights[column]++;
	b->lm++;
	b->moves[b->lm] = column;
	b->cp = -b->cp;
}

void undoMove(board_t *b)
{
	setState(b->grid[b->moves[b->lm]][b->heights[b->moves[b->lm]] - 1], (EMPTY));
	b->heights[b->moves[b->lm]]--;
	b->lm--;
	b->cp = -b->cp;
}

int getRandomPlayerMove(board_t *b)
{
	int val = -1;
	int possible[7];
	int i;
	
	for (i = 0; i < 7; i++)
	{
		if (validMove(b, i))
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
int getReasonedMove(board_t *cB)
{
	int moves[7];
	int highest = 0;
	int i;
	for(i = 0; i < 7; i++)
	{
		moves[i] = INT_MIN;
		
		if (validMove(cB, i))
		{
			makeMove(cB, i);
			moves[i] = minValue(cB, 4);
			
			if (moves[i] >= moves[highest])
			{
				highest = i;
			}
			undoMove(cB);
		} 
	}
	return highest;
}

int getStrength(board_t *b)
{
	int sum = 0;
	int weights[] = {0, 1, 10, 50, 600};
	int i;
	for (i = 0; i < 69; i++)
	{
		sum += (getScore(b->cl[i]) > 0) ? weights[abs(getScore(b->cl[i]))] : -weights[abs(getScore(b->cl[i]))];
	}
	return sum + (b->cp == PLAYER_ONE ? 16 : -16);
}

// don't change this unless you understand it
int minValue(board_t *cB, int ply)
{
	int moves[7];
	int lowest = 0;
	int i;
	
	for (i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		
		if (validMove(cB, i))
		{
			makeMove(cB, i);
			
			if ((winnerIs(cB) == 0) && ply > 0)
			{
				moves[i] = maxValue(cB, ply - 1);
			}
			else 
			{
				moves[i] = -getStrength(cB);
			}
			
			if (moves[i] < moves[lowest])
			{
				lowest = i;
			}
			undoMove(cB);
		}
	}
	return moves[lowest];
}

//careful with this
int maxValue(board_t *cB, int ply)
{
	int moves[7];
	int highest = 0;
	int i;
	
	for (i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		if (validMove(cB, i))
		{
			makeMove(cB, i);

			if ((winnerIs(cB) == 0) && ply > 0)
			{
				moves[i] = minValue(cB, ply - 1);
			}
			else
			{
				moves[i] = -getStrength(cB);
			}

			if (moves[i] < moves[highest])
			{
				highest = i;
			}
			
			undoMove(cB);
		}
	}
	return moves[highest];
}
