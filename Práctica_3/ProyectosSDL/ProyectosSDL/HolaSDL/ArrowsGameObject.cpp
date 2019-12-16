#include "ArrowsGameObject.h"
#include "PlayState.h"

ArrowsGameObject::ArrowsGameObject(Point2D pos, Vector2D velocity, double width, double height, Texture* texture, GameState* game, int id):
	SDLGameObject(pos, width, height, texture, game)
{
	vel = velocity;
	ID = id;
	playState = dynamic_cast<PlayState*>(game);
};

ArrowsGameObject::~ArrowsGameObject() {};

//void ArrowsGameObject::render()
//{
//	texture->render(getDestRect(1,1));
//}

void ArrowsGameObject::update()
{
	pos = { pos.getX() + (vel.getY() * vel.getX()), pos.getY() };
}

//SDL_Rect ArrowsGameObject::getDestRect(int cols, int rows)
//{
//	SDL_Rect destRect;
//	destRect.h = height/rows;
//	destRect.w = width/cols;
//	destRect.x = pos.getX();
//	destRect.y = pos.getY();
//	return destRect;
//}

SDL_Rect* ArrowsGameObject::getCollisionRect(int cols, int rows)
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX(), (int)height/rows, (int)width / cols };
}

//void ArrowsGameObject::setItList(list<GameObject*>::iterator iterator)
//{
//	it = iterator;
//}

void ArrowsGameObject::loadFromFile(fstream& input)
{
	double aux, aux2;
	input >> aux;
	input >> aux2;
	pos = { aux, aux2};
	input >> aux;
	input >> aux2;
	vel = { aux, aux2 };
	input >> width;
	input >> height;
}

void ArrowsGameObject::saveToFile(ofstream& output)
{
	output << ID << " " << pos.getX() << " " << pos.getY() << " " << vel.getX() << " "
		<< vel.getY() << " " << width << " " << height << " ";
}