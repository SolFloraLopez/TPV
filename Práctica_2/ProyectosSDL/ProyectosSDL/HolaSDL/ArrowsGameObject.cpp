#include "Game.h"
#include "ArrowsGameObject.h"

ArrowsGameObject::ArrowsGameObject(Point2D pos, Vector2D vel, double width, double height, Texture* texture, Game* game) : 
	pos(pos), width(width), height(height), vel(vel), texture(texture),  game(game) {};

ArrowsGameObject::~ArrowsGameObject() {};

void ArrowsGameObject::render()
{
	texture->render(getDestRect(1,1));
}

void ArrowsGameObject::update()
{
	pos = { pos.getX() + (vel.getY() * vel.getX()), pos.getY() };
}

SDL_Rect ArrowsGameObject::getDestRect(int cols, int rows)
{
	SDL_Rect destRect;
	destRect.h = height/rows;
	destRect.w = width/cols;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	return destRect;
}

SDL_Rect* ArrowsGameObject::getCollisionRect(int cols, int rows)
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX(), (int)height/rows, (int)width / cols };
}

void ArrowsGameObject::setItList(list<GameObject*>::iterator iterator)
{
	it = iterator;
}