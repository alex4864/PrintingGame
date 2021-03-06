#ifndef FUNCTIONS_H
#define FUNCTIONS_H	//keeps me from including functions twice

void print_layout(int day, int money, int power_up_days);
void print_end_day(int profit, int funds);
int find_revenue();
void buyPrinter();
char do_choice(char choice, int& money, bool PowerUp);
void powerUpCountdown(int& days);
void buyPowerUp(int& money, int power_up_days, bool PowerUp);

#endif
