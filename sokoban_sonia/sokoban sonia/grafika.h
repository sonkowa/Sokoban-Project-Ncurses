#pragma once
#include <ncursesw/curses.h>
#include <string>
class Grafika {
		WINDOW *okno;
		int height, width, startrow, startcol, xres, yres;
		int playerrow = 5;
		int playercol = 9;
		int levelrows = 9;
		int levelcols = 17;
		bool one = false, two = false, three = false, four = false, five = false;
		bool isdot = false;
		int dotposrow, dotposcol;
	public:
		Grafika() {}
		Grafika(int h, int w) : height(h), width(w) {
			inicjalizacja();
			mainmenu();
			rysujlevel();
		}
		void inicjalizacja() {
			initscr();
			noecho();
			curs_set(0);
			getmaxyx(stdscr, yres, xres);
			startrow = (yres / 2) - (height / 2);
			startcol = (xres / 2) - (width / 2);
			okno = newwin(height, width, startrow, startcol);
			box(okno, 0, 0);
			keypad(okno, true);
		}
		void mainmenu() {
			mvwaddstr(okno, 1, 2, "SOKOBAN");
			mvwaddstr(okno, 3, 2, "press 1 to start");
			while(getinput() != '1') {
				;
			}
			werase(okno);
			box(okno, 0, 0);
		}
		void rysujlevel() {
			std::string level =
			    "     #######     "
			    "######  .  ######"
			    "#  .   $#$   .  #"
			    "#               #"
			    "###$####@####$###"
			    "#               #"
			    "#  .   $#$   .  #"
			    "######  .  ######"
			    "     #######     ";
			for (int i = 0; i <= levelrows-1; ++i)
				for (int j = 0; j <= levelcols-1; ++j) {
					char ch = level[i * levelcols + j];
					mvwprintw(okno, i+1, j+1, "%c", ch);
				}
		}
		chtype getinput() {
			return wgetch(okno);
		}
		void draw(int row, int col, chtype sign) {
			mvwaddch(okno, row, col, sign);
		}
		void update() {
			wrefresh(okno);
			if(isdot == true && mvwinch(okno, dotposrow, dotposcol) == ' ') {
				draw(dotposrow, dotposcol, '.');
				isdot = false;
			}
		}
		void domove(int direction, bool col) {
			if (col) {
				if(mvwinch(okno, playerrow, playercol+direction) != '#' && mvwinch(okno, playerrow, playercol+direction) != '!') {
					if(mvwinch(okno, playerrow, playercol+direction) == '$') {
						if(mvwinch(okno, playerrow, playercol+direction+direction) != '#' && mvwinch(okno, playerrow, playercol+direction+direction) != '#') {
							if(mvwinch(okno, playerrow, playercol+direction+direction) == '.')
								dotyes(playerrow, playercol+direction+direction);
							else
								draw(playerrow, playercol+direction+direction, '$');
						} else
							goto pominreposition;
					}
					draw(playerrow, playercol, ' ');
					playercol += direction;

					if(mvwinch(okno, playerrow, playercol) == '.') {
						dotposcol = playercol;
						dotposrow = playerrow;
						isdot = true;
					}
					draw(playerrow, playercol, '@');
pominreposition:
					;
				}
			}
			if (!col)
				if(mvwinch(okno, playerrow+direction, playercol) != '#' &&  mvwinch(okno, playerrow+direction, playercol) != '!') {
					if(mvwinch(okno, playerrow+direction, playercol) == '$') {
						if(mvwinch(okno, playerrow+direction+direction, playercol) != '#' && mvwinch(okno, playerrow+direction+direction, playercol) != '!') {
							if(mvwinch(okno, playerrow+direction+direction, playercol) == '.')
								dotyes(playerrow+direction+direction, playercol);
							else
								draw(playerrow+direction+direction, playercol, '$');
						} else
							goto pominreposition2;
					}
					draw(playerrow, playercol, ' ');
					playerrow += direction;

					if(mvwinch(okno, playerrow, playercol) == '.') {
						dotposcol = playercol;
						dotposrow = playerrow;
						isdot = true;
					}
					draw(playerrow, playercol, '@');
pominreposition2:
					;
				}
		}
		void dotyes(int dotrow, int dotcol) {
			draw(dotrow, dotcol, '!');
			if(!one) {
				one = true;
				return;
			}
			if(!two) {
				two = true;
				return;
			}
			if(!three) {
				three = true;
				return;
			}
			if(!four) {
				four = true;
				return;
			}
			if(!five) {
				five = true;
				return;
			}
			werase(okno);
			box(okno, 0, 0);
			start_color();
			init_pair(1, COLOR_BLACK, COLOR_GREEN);
			attron(COLOR_PAIR(1));
			mvwaddstr(okno, 1, 2, "VICTORY");
			attroff(COLOR_PAIR(1));
			mvwaddstr(okno, 3, 2, "press q to exit");
		}
};