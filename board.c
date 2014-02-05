#include <stdlib.h>
#include "defines.h"
#include "point.h"
#include "board.h"

board_t *createBoard(int a, int b)
{
	board_t *p = (board_t*) malloc(sizeof(board_t));
	p->cols = a;
	p->rows = b;
	p->lm = -1;
	p->cp = PLAYER_ONE;
	p->heights = (int*) malloc(p->cols * sizeof(int));
	p->grid = (point_t***) malloc(p->cols * sizeof(point_t**));
	int x;
	int y;
	
	for (x = 0; x < p->cols; x++)
	{
		p->grid[x] = (point_t**) malloc(p->rows * sizeof(point_t*));
		p->heights[x] = 0;
		for (y = 0; y < p->rows; y++)
		{
			p->grid[x][y] = newPoint(x, y);
		}
	}
	p->moves = (int*) malloc(p->cols * p->rows * sizeof(int));

	p->cl = generateCL(p->grid);
	return p;
}

void deleteboard(board_t *p)
{
	free(p->cl);
	free(p->grid);
	free(p->heights);
	free(p->moves);
	free(p);
}

point_t ***generateCL(point_t ***grid)
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