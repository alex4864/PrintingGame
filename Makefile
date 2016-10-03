Money: main.o
	g++ main.o -o Money -lncurses
main.o: main.cpp
	g++ main.cpp -c

