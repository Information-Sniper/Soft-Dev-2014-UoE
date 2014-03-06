#include <stdlib.h>
#include "defines.h"
#include "point.h"

point_t *newPoint(int a, int b)
{
	point_t *p = (point_t*) malloc(sizeof(point_t));
	p->x = a;
	p->y = b;
	p->state = EMPTY;
	return p;
}

void deletepoint(point_t *p)
{
	free(p);
}

int equalsPosition(point_t *a, point_t *b)
{
	return a->x == b->x && a->y == b->y;
}

void setState(point_t *a, int player)
{
	a->state = player;
}

int getState(point_t *a)
{
	return a->state;
}