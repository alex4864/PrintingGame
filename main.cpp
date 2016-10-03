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

const char PRODUCER_CHAR[] = {'h', 'i', 'l', 'p'};
const std::string PRODUCER_NAME[] = {"Hand Writer", "Inkjet Printer", "Laser Printer", "Printing Press"};

const int HAND_WRITER_REV = 5;
const char HAND_WRITER_CHAR = 'h';
const int HAND_WRITER_COST = 75;

const int INKJET_PRINTER_REV = 15;
const char INKJET_PRINTER_CHAR = 'i';
const int INKJET_PRINTER_COST = 200;

const int LASER_PRINTER_REV = 40;
const char LASER_PRINTER_CHAR = 'l';
const int LASER_PRINTER_COST = 500;

const int PRINTING_PRESS_REV = 100;
const char PRINTING_PRESS_CHAR = 'p';
const int PRINTING_PRESS_COST = 1500;


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
	for (int lcv = 0; lcv <= sizeof(slot); lcv++) //checks for the revenue of each associated slot, adds all together
	{
		if (slot[lcv] == '1')
		{
			rev += HAND_WRITER_REV;
		}
			
		else if (slot[lcv] == '2')
		{
			rev += LASER_PRINTER_REV;
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
		printw("Options: \n\t%c : Hand-Writer costs $%i and makes $%i per day", HAND_WRITER_CHAR, HAND_WRITER_COST, HAND_WRITER_REV );
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

