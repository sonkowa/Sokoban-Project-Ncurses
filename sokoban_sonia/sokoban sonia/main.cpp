#include "sokoban.h"
#include <iostream>
#include <ncursesw/curses.h>
#define height 11
#define width 19
int main (int argc, char** argv) {
	reset:;
	Sokoban sokobans(height, width);
	while (!sokobans.isexit()) {
		sokobans.update();
		sokobans.getmove();	
	}
	if(sokobans.isreset())
		goto reset;
	
	getch();
	endwin();
	refresh();
	return 0;
}
