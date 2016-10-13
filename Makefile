Money: main.o functions.o
	g++ main.o functions.o -o Money -lncurses

functions.o: functions.cpp
	g++ functions.cpp -c

main.o: main.cpp
	g++ main.cpp -c
	
clean:
	rm Money main.o functions.o

