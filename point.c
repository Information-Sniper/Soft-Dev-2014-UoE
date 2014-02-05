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