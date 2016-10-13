#include<iostream>
#include<string>
#include<ncurses.h>
#include "functions.h"

/*		TO-DO LIST:
	Add all type of printers
	
	Create buy function to change slot value (need to specify a slot, which printer)
	
	Create sell function to set slot = x and return portion of cost
	
	Implement Rent function
*/



int main()
{
	initscr();
	printw("\n\n\tWelcome to the money game!\n\n Print money and buy more money printers!"); //Game start splash screen
	refresh();	
	getch();
	clear();
	
	
	int money = 100;
	bool game_run = true;
	while (game_run)
	{
		char user_choice = '\0';
		
		while (user_choice == '\0')
		{
			clear();
			print_layout();
			printw("Pick what you'd like to do: ");
			refresh();
			user_choice = getch();
			user_choice = do_choice(user_choice);
			getch();
		}
		print_end_day(find_revenue(), money);
		money += find_revenue();
		getch();
	}
	printw("Thank you for playing!");
	endwin();
	return 0;
}

