#include <stdlib.h>
#include "defines.h"
#include "point.h"
#include "board.h"
#include "game.h"

int getScore(point_t *points[])
{
	int playerone = 0;
	int playertwo = 0;
	int i;
	
	for (i = 0; i < 4; i++)
	{
		if (getState(points[i]) == PLAYER_ONE)
		{
			playerone++;
		}
		else if (getState(points[i]) == PLAYER_TWO)
		{
			playertwo++;
		}
	}

	if ((playerone + playertwo > 0) && (!(playerone > 0 && playertwo > 0)))
	{
		return (playerone != 0) ? playerone : playertwo;
	}
	else
	{
		return 0;
	}
	
/*	
	if (player_1 > 0 && player_2 == 0)
	{
		return player_1;
	}
	else if (player_2 > 0 && player_1 == 0)
	{
		return player_2;
	}
	else
	{
		return 0;
	}
*/
}

int winnerIs(board_t *b)
{
	int i;
	
	for (i = 0; i < 69; i++)
	{
		if (getScore(b->cl[i]) == 4)
		{
			return PLAYER_ONE;
		}
		else if (getScore(b->cl[i]) == -4)
		{
			return PLAYER_TWO;
		}
	}
	return 0;
}

int cp(board_t *b)
{
	return b->cp;
}

char *toString(board_t *b)
{
	char *temp = (char*) malloc(b->rows * (b->cols + 1) * sizeof(char) + 1);

	char *curr = temp;
	int y;
	int x;
	
	for (y = b->rows - 1; y > -1; y--)
	{
		for (x = 0; x < b->cols; x++)
		{
			if (getState(b->grid[x][y]) == EMPTY)
			{
				*curr = '-';
			}
			else if (getState(b->grid[x][y]) == PLAYER_ONE)
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