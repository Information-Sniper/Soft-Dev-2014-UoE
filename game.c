#include <stdlib.h>
#include "defines.h"
#include "point.h"
#include "board.h"
#include "game.h"

int get_score(point_t *points[])
{
	int player_1 = 0;
	int player_2 = 0;
	int i;
	
	for (i = 0; i < 4; i++)
	{
		if (get_state(points[i]) == PLAYER_ONE)
		{
			player_1++;
		}
		else if (get_state(points[i]) == PLAYER_TWO)
		{
			player_2--;
		}
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
 * get_score() always returns positive number.
 * winner_is() cannot return PLAYER_TWO
 */
int winner_is(board_t *b)
{
	int i;
	
	for (i = 0; i < POS_COMBOS; i++)
	{
		if (get_score(b->cl[i]) == 4)
		{
			return PLAYER_ONE;
		}
		else if (get_score(b->cl[i]) == -4)
		{
			return PLAYER_TWO;
		}
	}
	
	return NONE;
}

int get_current_player(board_t *b)
{
	return b->current_player;
}

char *to_string(board_t *b)
{
	char *temp = (char*) malloc(b->rows * (b->cols + 1) * sizeof(char) + 1);

	char *curr = temp;
	int x;
	int y;
	
	for (y = b->rows - 1; y > -1; y--)
	{
		for (x = 0; x < b->cols; x++)
		{
			if (get_state(b->grid[x][y]) == EMPTY)
			{
				*curr = '-';
			}
			else if (get_state(b->grid[x][y]) == PLAYER_ONE)
			{
				*curr = 'O';
			}
			else
			{
				*curr = 'X';
			}
			curr++;
		}
		*curr = '\n';
		curr++;
	}
	return temp;
}