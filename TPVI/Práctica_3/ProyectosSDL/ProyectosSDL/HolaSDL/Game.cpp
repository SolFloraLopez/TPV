#include "SDLApplication.h"

using namespace std;

using uint = unsigned int;

SDLApplication::SDLApplication() 
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr) throw "SDL Error \n";

	for (int i = 0; i < NUM_TEXTURES; i++) //Crea el array de texturas con las texturas de todo el juego
	{
		textures[i] = new Texture(renderer, INFOTEXT[i].route, INFOTEXT[i].rows, INFOTEXT[i].columns);
	}


	stateMachine = new GameStateMachine();
	stateMachine->pushState(new MainMenuState(this));
}

void SDLApplication::run() {//Bucle principal
	while (!SDL_QuitRequested() && !exit)
	{
		if (stateMachine->getFlag() != "") checkStateMachine();

		//GameState* s = stateMachine->currentState();
		stateMachine->currentState()->handleEvents();
		stateMachine->currentState()->update();
		render();

		SDL_Delay(1000 / FRAME_RATE);
	}
}

void SDLApplication::render() //Llama a los metodos render de los elementos del juego
{
	SDL_RenderClear(renderer);

	stateMachine->currentState()->render();

	SDL_RenderPresent(renderer);
};

void SDLApplication::handleEvents() //Llama a HandleEvents del bow mientras que exit sea false, mientras que el jugador no salga del juego
{

	//SDL_Event event;//

	//if (!events.empty())
	//{
	//	while (SDL_PollEvent(&event) && !exit) {

	//		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) exit = true;

	//		if (!recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
	//		{
	//			recordingInput = true;
	//		}

	//		if (recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
	//		{
	//			file += event.key.keysym.sym;
	//		}

	//		else if (recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	//		{
	//			recordingInput = false;
	//			saving = true;
	//		}

	//		list<EventHandler*>::iterator eh;

	//		eh = events.begin();

	//		while (eh != events.end())
	//		{
	//			(*eh)->handleEvent(event);
	//			++eh;
	//		}
	//	}
	//}//
}

bool SDLApplication::getExit()
{
	return exit;
}

void SDLApplication::exitGame()
{
	exit = true;
}

void SDLApplication::loadFromFile()
{
	stateMachine->setFlag("LoadState");
	/*string file;
	cout << "\n Codigo del archivo de guardado: ";
	cin >> file;
	stateMachine->changeState(new PlayState(this, true, file));*/
}

void SDLApplication::saveToFile()
{
	stateMachine->setFlag("Save");
}

Texture* SDLApplication::getTexture(int num)
{
	return textures[num];
}

SDLApplication::~SDLApplication() //Destructor del juego
{
	delete stateMachine;

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLApplication::Pause() 
{
	stateMachine->pushState(new PauseState(this));
}

void SDLApplication::Resume() {

	stateMachine->setFlag("Resume");
}

void SDLApplication::Play() 
{
	stateMachine->setFlag("PlayState");
}

void SDLApplication::goMainMenu() 
{
	stateMachine->setFlag("MainMenu");
}

void SDLApplication::End()
{
	stateMachine->setFlag("EndState");
}

void SDLApplication::checkStateMachine()
{
	string flag = stateMachine->getFlag();

	if (flag == "MainMenu")

	{
		stateMachine->popState();
		stateMachine->changeState(new MainMenuState(this));
		stateMachine->setFlag("");
	}
	else if (flag == "PlayState") 
	{
		stateMachine->changeState(new PlayState(this));
		stateMachine->setFlag("");
	}
	else if (flag == "LoadState") 
	{
		string file;
		cout << "\n Codigo del archivo de guardado: ";
		cin >> file;
		stateMachine->changeState(new PlayState(this, file));
		//stateMachine->setFlag("PlayState");
		stateMachine->setFlag("");
	}
	else if(flag == "Save")
	{
		stateMachine->popState();
		stateMachine->currentState()->saveToFile();
		stateMachine->pushState(new PauseState(this));
		stateMachine->setFlag("");
	}
	else if (flag == "Resume")
	{
		stateMachine->popState();
		stateMachine->setFlag("");
	}
	else if (flag == "EndState")
	{
		stateMachine->changeState(new EndState(this));
		stateMachine->setFlag("");
	}
}