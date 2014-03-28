#include <stdio.h>
#include "defines.h"
#include "board.h"

/*
 * Player 1 starts the game.
 * All arrays are empty.
 * last_move is -1, because it is an
 * index. When the first move is played,
 * it will be kept in moves[last_move],
 * which is moves[0]
 */
void board_init(board_t *b)
{
	INT8 x, y;

	b->last_move = -1;
	b->cur_plr = PLAYER_ONE;
	
	for (x = 0; x < X_DIM; x++)
	{
		for (y = 0; y < Y_DIM; y++)
		{
			b->grid[x][y] = NONE;
		}
		b->heights[x] = 0;
	}
}

/* 
 * Prints "O", "X" or "-", depending on the value
 * of the cell, for player 1, player 2 or none.
 * Also prints the column numbers at the bottom.
 */
void board_display(const board_t *b)
{
	int  i;
	int  j;
	char point;
	
	for (j = Y_DIM - 1; j >= 0; j--)
	{
		putchar('|');
		
		for (i = 0; i < X_DIM; i++)
		{
			point = b->grid[i][j];
			
			if (point == PLAYER_ONE)
			{
				putchar('O');
			}
			else if (point == PLAYER_TWO)
			{
				putchar('X');
			}
			else
			{
				putchar('-');
			}
		}
		puts("|");
	}
	
	putchar(' ');
	
	for (i = '1'; i <= '0' + X_DIM; i++)
	{
		putchar(i);
	}
	
	puts("\n");
}

int board_set_point(board_t *b, INT8 x, INT8 y, INT8 player)
{
	int error;

	if (x < 0 || x >= X_DIM ||
	    y < 0 || y >= Y_DIM)
	{
		error = ERR_OUT_OF_BOUNDS;
	}
	else if (player != PLAYER_ONE &&
	         player != PLAYER_TWO &&
	         player != NONE)
	{
		error = ERR_INVALID_INPUT;
	}
	else
	{
		b->grid[x][y] = player;
		error = ERR_SUCCESS;
	}
	
	return error;
}

int board_get_point(POINT *p, const board_t *b, INT8 x, INT8 y)
{
	int error;
	
	if (x < 0 || x >= X_DIM ||
	    y < 0 || y >= Y_DIM)
	{
		error = ERR_OUT_OF_BOUNDS;
	}
	else
	{
		*p = b->grid[x][y];
		error = ERR_SUCCESS;
	}
	
	return error;
}
