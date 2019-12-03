#include "Game.h"

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try{
		cout << "Pulse 0 para jugar y 1 para cargar partida\n";
		int input;
		cin >> input;

		if (input == 1) {
			bool cargado = false;
			while (!cargado) {
				cout << "Introduzca codigo de partida\n";
				cin >> input;
				try
				{					
					Game game = Game(true, to_string(input));
					game.render();
					game.run();
					cargado = true;
				}
				catch (const std::exception&)
				{
					cout << "Codigo de partida no valido\n";
					cargado = false;
				}
			}
		}
		
		else if (input == 0)
		{			
			Game game = Game(false, "");
			game.render();
			game.run();
		}
		
	}
	catch (const char* msg) 
	{
		cout << "\n" << msg;
	}

	system("pause");
	return 0;
}