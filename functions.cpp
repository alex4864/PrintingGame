#include<iostream>
#include<string>
#include<ncurses.h>
#include"functions.h"
#include<time.h>

char slot[6] = {'x','x','x','x','x','x'};
const int SLOTS = 6;

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





void print_layout(int day, int money, int power_up_days)
{
	/*	Prints the grid layout in form
		x	x	x
		x	x	x
	*/
	printw("\n\tDay: %i\tMoney: $%i\tPower Up Left: %i\n\n\t%c\t\t%c\t\t%c\n\n\t%c\t\t%c\t\t%c\n\nb: Buy Printers\tn: Next Day\t\n\n", day, money, power_up_days, slot[0], slot[1], slot[2], slot[3], slot[4], slot[5]);
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
		for (int level = 0; level <= NUM_PRINTER_VARIATIONS; level++)//checks if char stored in slot corresponds to a printer and then adds printer's rev
		{
			if (slot[lcv] == PRODUCER_CHAR[level])
			{
				rev += PRODUCER_REV[level];
			}
			
		}
	}
	return rev;
}

void buyPrinter(int& money)
{
	printw("Options:"); //Prints options
	for (int printer_index = 0; printer_index < NUM_PRINTER_VARIATIONS; printer_index++)
		{
			printw( "\n\t%c : %s costs $%i and makes $%i per day", PRODUCER_CHAR[printer_index], PRODUCER_NAME[printer_index], 
				PRODUCER_COST[printer_index], PRODUCER_REV[printer_index]);
		}
	printw("\nChoice: ");
	char choice = getch();
	int choice_index_val = -1;
	for (int printer_index = 0; printer_index <= NUM_PRINTER_VARIATIONS; printer_index++)	//Sets the choice_index_val to corresponding val associated with char
	{
		if (choice == PRODUCER_CHAR[printer_index])
		{
			choice_index_val = printer_index;
		}
	}
	if (choice_index_val == -1) // if they give invalid input, returns out of FN without carrying on (add a pls try again later)
	{
		return;
	}
	printw("\nYou chose %c, it's the %s which cost %i\nWould you like to purchase this?(y/n): ",
		choice, PRODUCER_NAME[choice_index_val], PRODUCER_COST[choice_index_val]);
	char confirm = '\0';
	confirm = getch();
	if (confirm == 'y')
	{
		if (money >= PRODUCER_COST[choice_index_val])
		{
			printw("\nWhich slot will it occupy?: ");
			int slot_choice = -1;
			slot_choice = getch();
			slot_choice = slot_choice - 48;
			if (slot_choice <= SLOTS && slot_choice >= 0)
			{
				slot[slot_choice] = choice;
				money -= PRODUCER_COST[choice_index_val];
			}
			else
			{
				printw("\nInvalid slot number");
			}
		}
		else
		{
			printw("\nNot enough money");
		}
	}
	else
	{
		printw("\nAborting purchase!");
	}	
}

void buyPowerUp(int& money, int power_up_days, bool PowerUp)
{
	srand(time(NULL));
	if (power_up_days != 0)	//Makes sure that the user isn't currently using a power up
	{
		printw("Sorry! Wait for current power up to end!");
		return;
	}
	printw("Would you like to purchase a Power-Up for $100?(y/n)"); //Confirms user choice
	char confirm = '\0';
	confirm = getch();
	if (confirm == 'y')
	{
		money -= 100;
		int chance = rand() % 100;  //Gets a random num on [0,99] used to pick powerup
		if(chance == 0)
		{
			PowerUp[0] = true;
			printw("You got PowerUp 1");
		}
		else if(chance <=5)
		{
			PowerUp[1] = true;
			printw("You got PowerUp 2");
		}
		else if(chance <= 15)
		{
			PowerUp[2] = true;
			printw("You got PowerUp 3");
		}
		else if(chance <= 50)
		{
			PowerUp[3] = true;
			printw("You got PowerUp 4");
		}
		else
		{
			printw("You got nothing!!!");
		}
		return;
	}	
	else
	{
		return;
	}
}

void powerUpCountdown(int& days)
{
	if (days > 0)
	{
		days -= 1;
	}
}		
char do_choice(char choice, int& money, bool PowerUp) //Takes the user's char input and runs an if statement dependant on it
{	
	printw("\n");
	//Buy thing
	if (choice == 'b')
	{
		buyPrinter(money);
		
	}
	//Next day
	else if (choice == 'n')
	{
		printw("you chose n");
		return 'n'; // breaks while loop in main, leading to end of user choices
	}
	
	//Buy Powerups
	else if (choice == 'p')
	{
		buyPowerUp(money, power_up_days, PowerUp);
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

