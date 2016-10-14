#include<iostream>
#include<string>
#include<ncurses.h>
#include "functions.h"

/*		TO-DO LIST:
	Add all type of printers
	
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
	
	int day = 1;
	int money = 100;
	int power_up_left = 0;
	bool PowerUp[] = {false, false, false, false};
	bool game_run = true;
	while (game_run)
	{
		char user_choice = '\0';
		
		while (user_choice == '\0')
		{
			clear();
			print_layout(day, money, power_up_left);
			printw("Pick what you'd like to do: ");
			refresh();
			user_choice = getch();
			user_choice = do_choice(user_choice, money, PowerUp);
			getch();
		}
		money += find_revenue();
		print_end_day(find_revenue(), money);
		getch();
		powerUpCountdown(power_up_left);
		day += 1;
	}
	printw("Thank you for playing!");
	endwin();
	return 0;
}

