#ifndef DEFINES_H
#define DEFINES_H

/* User defined values 
 *
 * The dimensions of the board
 * X: horizontal
 * Y: vertical
 */
#define X_DIM 7
#define Y_DIM 6

/* Do not put this more than 5 */
#define DIFFICULTY  4

/* min and max macros */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* define char as 8-bit int */
#define INT8 char

/*
 * POINT and FOUR are defined for
 * convenience and understanding
 */
#define POINT INT8
#define FOUR  4

/* These are defined for consistency */
#define ROWS Y_DIM
#define COLS X_DIM

/* Player values */
#define PLAYER_ONE  1
#define PLAYER_TWO -1
#define NONE		0
#define COMPUTER	1
#define HUMAN		2


/* The 4 directions a player can win */
typedef enum
{
	HORIZONTAL = 0,
	VERTICAL,
	DOWNLEFT_UPRIGHT,
	UPLEFT_DOWNRIGHT,
	DIRECTIONS
} directions;

/* Error values */
typedef enum
{
	ERR_SUCCESS = 0,
	ERR_INVALID_INPUT,
	ERR_OUT_OF_BOUNDS,
	ERR_NO_MOVES
} errors;

#endif // DEFINES_H
