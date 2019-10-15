#include "Game.h"

int main(int argc, char* argv[]) {
	Game game = Game();
	game.render();
	game.run();
	return 0;
}