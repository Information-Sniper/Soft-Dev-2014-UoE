#include <stdlib.h>
#include "defines.h"
#include "point.h"

point_t *new_point(int x, int y)
{
	point_t *p = (point_t*) malloc(sizeof(point_t));
	p->x = x;
	p->y = y;
	p->state = EMPTY;
	return p;
}

void delete_point(point_t *p)
{
	free(p);
}

int equals_position(point_t *a, point_t *b)
{
	return a->x == b->x && a->y == b->y;
}

void set_state(point_t *p, int player)
{
	p->state = player;
}

int get_state(point_t *p)
{
	return p->state;
}