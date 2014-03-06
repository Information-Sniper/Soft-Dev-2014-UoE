#ifndef POINT_H
#define POINT_H

typedef struct point
{
	int x;
	int y;
	int state;
} point_t;

point_t *newPoint(int a, int b);
void     deletepoint(point_t *p);
void     setState(point_t *a, int player);
int      getState(point_t *a);
int      equalsPosition(point_t *a, point_t *b);

#endif // POINT_H
