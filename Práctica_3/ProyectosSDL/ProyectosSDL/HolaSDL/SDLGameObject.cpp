#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(Point2D pos, double width, double height, Texture* texture, Game* gameState): 
	pos(pos), width(width), height(height), texture(texture), game(gameState){}

void SDLGameObject::render()
{
	texture->render(getDestRect(1, 1));
}

SDL_Rect SDLGameObject::getDestRect(int cols, int rows)
{
	SDL_Rect destRect;
	destRect.h = height / rows;
	destRect.w = width / cols;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	return destRect;
}

void SDLGameObject::setItList(list<GameObject*>::iterator iterator)
{
	it = iterator;
}