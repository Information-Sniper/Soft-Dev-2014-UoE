#include <stdlib.h>
#include "defines.h"
#include "point.h"
#include "board.h"

board_t *create_board(int x, int y)
{
	board_t *b = (board_t*) malloc(sizeof(board_t));
	int i;
	int j;
	
	b->cols = x;
	b->rows = y;
	b->lm = -1;
	b->current_player = PLAYER_ONE;
	b->heights = (int*) malloc(x * sizeof(int));
	b->grid = (point_t***) malloc(x * sizeof(point_t**));

	
	for (i = 0; i < x; i++)
	{
		b->grid[i] = (point_t**) malloc(y * sizeof(point_t*));
		b->heights[i] = 0;
		
		for (j = 0; j < y; j++)
		{
			b->grid[i][j] = new_point(i, j);
		}
	}
	b->moves = (int*) malloc(x * y * sizeof(int));

	b->cl = generate_CL(b->grid);
	
	return b;
}

void delete_board(board_t *b)
{
	free(b->cl);
	free(b->grid);
	free(b->heights);
	free(b->moves);
	free(b);
}

point_t ***generate_CL(point_t ***grid)
{
	point_t ***lines = (point_t***) malloc(69 * sizeof(point_t**));
	int i;
	
	for (i = 0; i < 69; i++)
	{
		lines[i] = (point_t**) malloc(4 * sizeof(point_t*));
	}

	int count = 0;
	int y;
	int x;
	int t;
	
	for (y = 0; y < 6; y++)
	{
		for (x = 0; x < 4; x++)
		{
			point_t **temp = (point_t**) malloc(4 * sizeof(point_t*));
			for (i = x; i < x + 4; i++)
			{
				temp[i - x] = grid[i][y];
			}
			lines[count] = temp;
			count++;			
		}
	}

	for (x = 0; x < 7; x++)
	{
		for (y = 0; y < 3; y++)
		{
			point_t **temp = (point_t**) malloc(4 * sizeof(point_t*));
			for (i = y; i < y + 4; i++)
			{
				temp[i - y] = grid[x][i];
			}
			lines[count] = temp;
			count++;
		}

	}

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 3; y++)
		{
			point_t **temp = (point_t**) malloc(4 * sizeof(point_t*));
			for (t = x, i = y; t < x + 4 && i < y + 4; t++, i++)
			{
				temp[i - y] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	
	for (x = 0; x < 4; x++)
	{
		for (y = 5; y > 2; y--)
		{
			point_t **temp = (point_t**) malloc(4 * sizeof(point_t*));
			for (t = x, i = y; t < x + 4 && i > -1; t++, i--)
			{
				temp[t - x] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	return lines;
}