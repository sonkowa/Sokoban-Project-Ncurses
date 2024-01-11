#pragma once
#include "grafika.h"
#include <ncursesw/curses.h>
class Sokoban {
		Grafika graphic;
		bool exit=false, reset=false;

	public:

		Sokoban(int height, int width);
		void loadLevel();
		void useinput();
		void position();
		void update();
		bool isexit();
		bool victory();
		void getmove();
		bool isreset();
};