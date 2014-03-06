#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect4.h"

int main(int argc, char **argv) 
{
	int input;
	board_t *b = create_board(COLS, ROWS);

	srand(time(NULL));
	
	while((winner_is(b) == NONE) && valid_moves_left(b))
	{
		if(get_current_player(b) == PLAYER_ONE)	
		{
			scanf("%d", &input);
			make_move(b, input);	// Make it so!
		}
		else
		{
			make_move(b, get_reasoned_move(b));	// Make it so!
		}

		printf("%s\n", to_string(b));
	}
	
	return 0;
}
