#include "Game.h"

using namespace std;

using uint = unsigned int;

SDLApplication::SDLApplication(bool load, string route) 
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

	//ScoreBoard* scoreBoard = new ScoreBoard(textures[DigitsTexture], textures[ScoreArrowTexture], this);
	//objects.push_back(scoreBoard);
	//scoreBoard->setItList(objects.end());

	//if (!load) {
	//	Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,
	//		{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this, 0); //Crea el arco

	//	objects.push_back(bow);
	//	events.push_back(bow);
	//	bow->setItList(objects.end());

	//	butterflyspawner();
	//}
	//else {
	//	loadFromFile(route);
	//}
}

void SDLApplication::run() {//Bucle principal
	while (!SDL_QuitRequested() && !exit)
	{
		handleEvents();
		update();
		render();
		SDL_Delay(1000 / FRAME_RATE);
	}
}

void SDLApplication::render() //Llama a los metodos render de los elementos del juego
{
	SDL_RenderClear(renderer);
	//textures[currentMap % MAP_AMOUNT]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	//list<GameObject*>::iterator it;//

	//it = objects.begin();

	//while (it != objects.end())
	//{
	//	(*it)->render();
	//	++it;
	//}//
	
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

void SDLApplication::update() //Llama a los update de los elementos del juego, si estos devuelven false se elimina el elemento correspondiente
{
	//if (saving) {//
	//	saveToFile();
	//}

	//list<GameObject*>::iterator it;
	//GameObject* aux;

	//it = objects.begin();

	//while (it != objects.end())
	//{
	//	(*it)->update();
	//	++it;
	//}

	//if (points >= currentMaxPoints)
	//{
	//	it = next(objects.begin(), 2);
	//	int j = objects.size();

	//	for (int i = 2; i < j; i++)
	//	{
	//		aux = *it;
	//		if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
	//		it = objects.erase(it);
	//		delete aux;
	//	}

	//	currentMap++;
	//	currentMaxPoints += BASE_POINT_MAX * ((currentMap % MAP_AMOUNT) + 1);
	//	availableArrows = BASE_ARROWS_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);
	//	butterflyspawner();
	//}

	//if(!objectsToErase.empty()) 
	//{
	//	it = *objectsToErase.begin();

	//	for(int i = 0; i < objectsToErase.size(); i++)
	//	{
	//		aux = *it;
	//		if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
	//		it = objects.erase(it);
	//		delete aux;
	//	}

	//	objectsToErase.clear();
	//}

	//if (currentButterflies <= 0) exit = true;//
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
	stateMachine->currentState()->loadFromFile();

	//fstream input(route);

	//input >> availableArrows; input >> currentButterflies; input >> currentArrows; input >> points;
	//input >> currentMap; input >> currentMaxPoints;

	//ScoreBoard* scoreBoard = new ScoreBoard(textures[DigitsTexture], textures[ScoreArrowTexture], this);
	//objects.push_back(scoreBoard);
	//scoreBoard->setItList(objects.end());

	//int size, aux;
	//input >> size;

	//for(int i = 0; i < size; i++)
	//{
	//	input >> aux;
	//	switch (aux)
	//	{
	//	case 0:
	//	{Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,
	//		{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this, 0); //Crea el arco

	//	objects.push_back(bow);
	//	events.push_back(bow);
	//	bow->setItList(objects.end());
	//	bow->loadFromFile(input);
	//	break; }
	//	case 1:
	//	{Butterfly* newButterfly = new Butterfly({ 0, 0 }, { 0, 0 }, (double)0, (double)0, true, textures[ButterflyTexture], this, 1);
	//	newButterfly->setItList(objects.insert(objects.end(), newButterfly));
	//	newButterfly->loadFromFile(input);
	//	break; }
	//	case 2:
	//	{Reward* newReward = new Reward({ 0, 0 }, { 0, 0 },
	//		(double)0, (double)0, true, 0, textures[RewardTexture], textures[BubbleTexture], nullptr, this, 2);
	//	newReward->setItList(objects.insert(objects.end(), newReward));
	//	events.push_back(newReward);
	//	newReward->loadFromFile(input);
	//	break; }
	//	case 3:
	//	{Balloon* newBalloon = new Balloon({ 0, 0 }, (double)0, (double)0, { 0, 0 }, true, textures[Balloons], 0, this, 3);
	//	newBalloon->setItList(objects.insert(objects.end(), newBalloon));
	//	newBalloon->loadFromFile(input);
	//	break; }
	//	case 4:
	//	{Arrow* arrow = new Arrow(0, 0, { 0, 0 }, { 0, 0 }, textures[ArrowTexture], this, 4);
	//	shotArrows.push_back(arrow);
	//	arrow->setItList(objects.insert(objects.end(), arrow));
	//	arrow->loadFromFile(input);
	//	break; }
	//	default:
	//		break;
	//	}
	//}

	//input.close();
}

void SDLApplication::saveToFile()
{
	stateMachine->popState();
	stateMachine->currentState()->saveToFile();
	stateMachine->pushState(new PauseState(this));
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
