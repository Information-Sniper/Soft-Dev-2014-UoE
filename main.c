#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"

int main(void) 
{
	INT8    input;
	INT8    winner;
	INT8    player_2;
	INT8    flag;
	board_t b;
	
	board_init(&b);
	puts("\nWelcome to a new game of connect 4!\n");
	fputs("Press 1 to play against the computer, or 2 to play against a friend: ", stdout);
	
	while(get_user_input(&input, 2))
	{
		fputs("Invalid input. Please choose between 1 and 2: ", stdout);
	}

	player_2 = input - 1;
	
	board_display(&b);
	
	do
	{
		if (get_current_player(&b) == PLAYER_ONE)	
		{
			do
			{
				fputs("Player 1 turn: ", stdout);
			
				if (!get_user_input(&input, COLS))
				{
					if (valid_move(&b, input))
					{
						flag = 0;
					}
					else
					{
						printf("Column %d is full\n", input);
						flag = 1;
					}
				}
				else
				{
					puts("Invalid input");
					printf("You have to input a number between 1 and %d\n", COLS);
					flag = 1;
				}
			} while (flag);
		}
		else
		{
			if (!player_2)  /* vs. computer */
			{
				input = get_reasoned_move(&b);
				printf("Computer played: %d\n", input);
			}
			else
			{
				fputs("Player 2 turn: ", stdout);
				
				while (get_user_input(&input, COLS))
				{
					puts("Invalid input");
					printf("You have to input a number between 1 and %d\n", COLS);
					fputs("Player 2 turn: ", stdout);
				}
			}
		}
		
		make_move(&b, input);
		board_display(&b);
		winner = winner_is(&b);
		
	} while (winner == NONE && valid_moves_left(&b));

	if (winner == PLAYER_ONE)
	{
		if (!player_2)
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
		if (!player_2)
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
