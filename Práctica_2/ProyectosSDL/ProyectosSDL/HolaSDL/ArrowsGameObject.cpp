#include "Game.h"
#include "ArrowsGameObject.h"

ArrowsGameObject::ArrowsGameObject(Point2D pos, Vector2D vel, double width, double height, Texture* texture, Game* game) : 
	pos(pos), width(width), height(height), vel(vel), texture(texture),  game(game) {};

ArrowsGameObject::~ArrowsGameObject() {};

void ArrowsGameObject::render()
{
	texture->render(getDestRect());
}

bool ArrowsGameObject::update()
{
	pos = { pos.getX() + (vel.getY() * vel.getX()), pos.getY() };
	return true;
}

SDL_Rect ArrowsGameObject::getDestRect()
{
	SDL_Rect destRect;
	destRect.h = height;
	destRect.w = width;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	return destRect;
}

SDL_Rect* ArrowsGameObject::getCollisionRect()
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX() + (int)width, (int)height, (int)width };
}