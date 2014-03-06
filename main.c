#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect4.h"

int main(int argc, char **argv) 
{
	srand(time(NULL));
	board_t *b = create_board(7, 6);

	int input;
	
	while((winner_is(b) == 0) && valid_moves_left(b))
	{
		if(cp(b) == PLAYER_ONE)	
		{
			scanf("%d", &input);
			make_move(b, input);// Make it so!
		}
		else
		{
			make_move(b, get_reasoned_move(b));// Make it so!
		}

		printf("%s\n", to_string(b));
	}
	
	return 0;
}
