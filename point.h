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

#endif // POINT_H
