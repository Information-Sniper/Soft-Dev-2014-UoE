#ifndef POINT_H
#define POINT_H

typedef struct point
{
	int x;
	int y;
	int state;
} point_t;

point_t *new_point(int x, int y);
void     delete_point(point_t *p);
void     set_state(point_t *p, int player);
int      get_state(point_t *p);
int      equals_position(point_t *a, point_t *b);

#endif // POINT_H
