#include "Game.h"

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try{
		Game game = Game();
		game.render();
		game.run();
	}
	catch (const char* msg) 
	{
		cout << "\n" << msg;
	}

	system("pause");
	return 0;
}