#include "sokoban.h"
Sokoban::Sokoban(int height, int width) {
	graphic = Grafika(height, width);
	graphic.inicjalizacja();
	graphic.rysujlevel();
}
void Sokoban::update() {
	graphic.update();
}
bool Sokoban::isexit() {
	return exit;
}
bool Sokoban::isreset(){
	return reset;
}
void Sokoban::getmove() {
	chtype input = graphic.getinput();

	switch (input) {
		case KEY_UP:
		case 'w':
			graphic.domove(-1, false);
			break;
		case KEY_DOWN:
		case 's':
			graphic.domove(1, false);
			break;
		case KEY_RIGHT:
		case'd':
			graphic.domove(1, true);
			break;
		case KEY_LEFT:
		case 'a':
			graphic.domove(-1, true);
			break;
		case 'r':
			reset = true;
			exit = true;
			break;
		case 'q':
			exit = true;
			break;
		default:
			break;
	}
}