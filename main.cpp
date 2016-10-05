#include<iostream>
#include<string>
#include<ncurses.h>

/*		TO-DO LIST:
	Add all type of printers
	
	Create buy function to change slot value (need to specify a slot, which printer)
	
	Create sell function to set slot = x and return portion of cost
	
	Implement Rent function
*/


char slot[6] = {'x', 'x','x','x','x','x'};
int money = 100;

/*
Each printer has an associated array value eg. HandWriter = 0, Printing Press = 3
Properties of each printer are stored at index of the printer in each different propery's array
(I feel like there's a better way to do this with classes, but I don't actually know yet)
*/
const int NUM_PRINTER_VARIATIONS = 4;
const char PRODUCER_CHAR[] = {'h', 'i', 'l', 'p'};
	
//2D Array of chars, List of strings (which are a list of chars)	
	const char PRINTER_0[] = "Hand Writer";
	const char PRINTER_1[] = "Inkjet Printer";
	const char PRINTER_2[] = "Laser Printer";
	const char PRINTER_3[] = "Printing Press";
const char* PRODUCER_NAME[] = {PRINTER_0, PRINTER_1, PRINTER_2, PRINTER_3};

const int PRODUCER_COST[] = {75, 200, 500, 1500};
const int PRODUCER_REV[] = {5, 15, 40, 100};





void print_layout()
{
	printw("\n\t%c\t%c\t%c\n\t%c\t%c\t%c\n\n", slot[0], slot[1], slot[2], slot[3], slot[4], slot[5]);
	refresh();
}

void print_end_day(int profit, int funds)
{
	printw("You earned $%i today for a total of $%i", profit, funds);
	refresh();
}


int find_revenue() //Adds up the value of all slots
{
	int rev = 0;
	for (int lcv = 0; lcv <= 5; lcv++) //checks for the revenue of each associated slot, adds all together
	{
		for (int level = 0; lcv <= NUM_PRINTER_VARIATIONS; level++)//checks if char stored in slot corresponds to a printer and then adds printer's rev
		{
			if (slot[lcv] == PRODUCER_CHAR[level])
			{
				rev += PRODUCER_REV[level];
			}
			
		}
	}
	return rev;
}


		
char do_choice(char choice) //Takes the user's char input and runs an if statement dependant on it
{	
	printw("\n");
	//Buy thing
	if (choice == 'b')
	{
		printw("Options:");
		for (int printer_index = 0; printer_index <= NUM_PRINTER_VARIATIONS; printer_index++)
		{
			printw( "\n\t%c : %s costs $%i and makes $%i per day", PRODUCER_CHAR[printer_index], PRODUCER_NAME[printer_index], PRODUCER_COST[printer_index], PRODUCER_REV[printer_index]);
		}
	}
	//Next day
	else if (choice == 'n')
	{
		printw("you chose n");
		return 'n'; // breaks while loop in main, leading to end of user choices
	}
	
	//Sell printer
	else if (choice == 's')
	{
		printw("you chose s");
	}
	
	//Invalid Selection
	else
	{
		printw("Please select a valid option: ");
		
	}
	refresh();
	return '\0';
}

int main()
{
	initscr();
	printw("\n\n\tWelcome to the money game!\n\n Print money and buy more money printers!"); //Game start splash screen
	refresh();	
	getch();
	clear();

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
			user_choice = 	do_choice(user_choice);
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

