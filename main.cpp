#include<iostream>
#include<ncurses.h>
using namespace std;
int main(int argc, char ** argv){
	initscr();
	mvprintw(30,10,"hello world");
	refresh();
	getch();
	endwin();
	return 0;
}
