#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"

int main(void) 
{
	INT8    move;
	INT8    winner;
	INT8    player_2;
	board_t b;
	
	board_init(&b);
	puts("\nWelcome to a new game of connect 4!\n");
	fputs("Press 1 to play against the computer, or 2 to play against a friend: ", stdout);
	
	while(get_user_input(&player_2, 2))
	{
		fputs("Invalid input. Please choose between 1 and 2: ", stdout);
	}
	
	board_display(&b);
	
	do
	{
		if (get_current_player(&b) == PLAYER_ONE)	
		{
			move = human_player(&b, PLAYER_ONE);
		}
		else
		{
			if (player_2 == COMPUTER)
			{
				move = computer_player(&b);
			}
			else
			{
				move = human_player(&b, PLAYER_TWO);
			}
		}
		
		make_move(&b, move);
		board_display(&b);
		winner = winner_is(&b);
		
	} while (winner == NONE && valid_moves_left(&b));

	if (winner == PLAYER_ONE)
	{
		if (player_2 == COMPUTER)
		{
			puts("Congratulations! You won!");
		}
		else
		{
			puts("Player 1 wins!");
		}
	}
	else if (winner == PLAYER_TWO)
	{
		if (player_2 == COMPUTER)
		{
			puts("You lost...");
		}
		else
		{
			puts("Player 2 wins!");
		}
	}
	else
	{
		puts("It's a tie! Close enough..");
	}
	
	puts("\nThe game will now exit. Hope to see you soon!\n");
	
	return EXIT_SUCCESS;
}
