#include <stdio.h>
#include <time.h>
#include "connect4.h"

int main(int argc, char **argv) 
{
	srand(time(NULL));
	board_type *b = createBoard(7, 6);

	int input;
	
	while((winnerIs(b) == 0) && validMovesLeft(b))
	{
		if(cp(b) == PLAYER_ONE)	
		{
			scanf("%d", &input);
			makeMove(b, input);// Make it so!
		}
		else
		{
			makeMove(b, getReasonedMove(b));// Make it so!
		}

		printf("%s\n", toString(b));
	}
	
	return 0;
}
