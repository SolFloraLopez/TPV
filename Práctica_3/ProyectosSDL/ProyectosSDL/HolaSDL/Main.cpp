#include "Game.h"

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	SDLApplication game = SDLApplication();
	game.render();
	game.run();
		
	system("pause");
	return 0;
}