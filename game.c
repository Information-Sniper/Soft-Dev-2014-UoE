#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "board.h"
#include "move.h"
#include "game.h"

/*
 * Checks all combinations that contain the last played
 * token. If in one of these, all tokens belong to the 
 * last player, the function returns it. Else, the 
 * function returns NONE.
 */
INT8 winner_is(const board_t *b)
{
	INT8   last_player = get_last_player(b);
	INT8   combos;
	POINT *point;
	INT8   i, j;
	INT8   incr;
	int    dir;

	if (b->last_move < 0)
	{
		return NONE;
	}
	
	for (dir = HORIZONTAL; dir < DIRECTIONS; dir++)
	{
		get_window(&combos, &point, &incr, b, dir);
		
		for (i = 0; i < combos; i++)
		{
			for (j = 0; j < FOUR; j++)
			{
				/*
				 * This is a bit hacky, but also clever.
				 * "point" points to the first value of 
				 * a combo. If we increment it by the 
				 * right amount, we can find the other
				 * 3 points that make the line.
				 */
				if (point[j * incr] != last_player)
				{
					break;
				}
			}
			
			if (j == FOUR)
			{
				return last_player;	
			}
			
			point += incr;
		}
	}
	
	return NONE;
}

INT8 get_current_player(const board_t *b)
{
	return b->cur_plr;
}

INT8 get_last_player(const board_t *b)
{
	return -b->cur_plr;
}

INT8 human_player(const board_t *b, INT8 player)
{
	INT8 input;
	INT8 flag;
	
	player = (player == PLAYER_ONE) ? 1 : 2;

	do
	{
		printf("Player %d turn: ", player);
	
		if (!get_user_input(&input, COLS))
		{
			if (valid_move(b, input - 1))
			{
				flag = 0;
			}
			else
			{
				printf("Column %d is full\n", input);
				flag = 1;
			}
		}
		else
		{
			puts("Invalid input");
			printf("You have to input a number between 1 and %d\n", COLS);
			flag = 1;
		}
	} while (flag);
	
	return input - 1;
}

INT8 computer_player(const board_t *b)
{
	INT8 move = get_reasoned_move(b);
	printf("Computer played: %d\n", move + 1);
	
	return move;
}

/*
 * Using strtod() we can have a parser
 * basically for free, without having
 * to worry about the user inputing 
 * legitimate numbers in "weird formats"  
 * and discard them. Just for the sake 
 * of completeness.
 */

int get_user_input(INT8 *input, INT8 max)
{
	char   buf[32];
	char  *rem_str;
	int    error;
	double num;

	fgets(buf, 32, stdin);
	
	num = strtod(buf, &rem_str);

	if ((rem_str[0] == '\0'  ||   /* 1) if the whole string */
	     rem_str[1] == '\0') &&   /*    is a number         */
	    !(num - (int) num)   &&   /* 2) if it is an integer */
		num > 0.0            &&   /* 3) if positive         */
		(INT8) num <= max)        /* 4) up to "max"         */

	{
		*input = (INT8) num;
		error = ERR_SUCCESS;
	}
	else
	{
		error = ERR_INVALID_INPUT;
	}
	
	return error;
}

/*
 * This function does some horrible number manipulation
 * to discover the number of combos that are possible 
 * from the last token played for a direction. It basically
 * calculates which should be the starting point, and how
 * many times the "mask of 4" can move in "direction"
 * without going out of bounds.
 */
static int get_window(INT8 *combos, POINT **p, INT8 *ptr_incr,
			          const board_t *b, int direction)
{
	INT8 x = b->moves[b->last_move];
	INT8 y = b->heights[x] - 1;
	INT8 start_x;
	INT8 start_y;
	INT8 tmp;
	int error = ERR_SUCCESS;

	switch (direction)
	{
	case HORIZONTAL:
		start_x = MAX(x - (FOUR - 1), 0);
		start_y = y;
		*combos = MIN(x - start_x + 1,
                      COLS - (start_x + FOUR - 1));
		*ptr_incr = Y_DIM;
		break;
	case VERTICAL:
		start_x = x;
		start_y = MAX(y - (FOUR - 1), 0);
		*combos = MIN(y - start_y + 1,
		              Y_DIM - (start_y + FOUR - 1));
		*ptr_incr = 1;
		break;
	case DOWNLEFT_UPRIGHT:
		tmp = MIN(MIN(x, y), FOUR - 1);
		start_x = x - tmp;
		start_y = y - tmp;
		
		*combos = MIN(MIN(x - start_x + 1,
                          COLS - (start_x + FOUR - 1)),
					  MIN(y - start_y + 1,
		                  Y_DIM - (start_y + FOUR - 1)));
		
		*ptr_incr = Y_DIM + 1;
		break;
	case UPLEFT_DOWNRIGHT:
		tmp = MIN(MIN(x, Y_DIM - y - 1), FOUR - 1);
		start_x = x - tmp;
		start_y = y + tmp;
		
		*combos = MIN(MIN(x - start_x + 1,
                          COLS - (start_x + FOUR - 1)),
					  MIN(start_y - y + 1,
					      start_y - (FOUR - 1) + 1));
	  
		*ptr_incr = Y_DIM - 1;
		break;
	default:
		error = ERR_INVALID_INPUT;
		break;
	}

	*p = &(b->grid[start_x][start_y]);
	
	if (*combos < 0)
	{
		*combos = 0;
	}
	
	return error;
}
