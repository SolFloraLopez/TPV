#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(double height, double width, Point2D pos, Vector2D vel, Texture* tex, GameState* game, int id) :
	ArrowsGameObject(pos, vel, width, height, tex, game, id) {}; //Constructor

Arrow::~Arrow() //Destructor
{}


void Arrow::update() //Mueve la flecha segun su posicion y velocidad
{
	pos = { pos.getX() + (vel.getY() * vel.getX()), pos.getY()};
	
	if (pos.getX() - width > WIN_WIDTH)
	{
		if (playState->changeCurrentArrows(-1) <= 0 && playState->changeAvaliableArrows(0) <= 0) game->exitGame();
		playState->killObject(it);
	}
}

void Arrow::changePos(Vector2D newPos) //Cambia la posicion de la flecha
{
	pos = { newPos.getX(), newPos.getY() };
}

SDL_Rect* Arrow::returnPointRect() //Devuelve el rectangulo de la punta de la flecha
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX() + ((int)width / 4) * 3 , (int)height / 2, (int)width / 4};
}

void Arrow::addHit()
{
	numHits++;
}

int Arrow::getHits()
{
	return numHits;
}

void Arrow::loadFromFile(fstream& input)
{
	ArrowsGameObject::loadFromFile(input);
}

void Arrow::saveToFile(ofstream& output)
{
	ArrowsGameObject::saveToFile(output);
}