#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(Point2D pos, double width, double height, Texture* texture, Game* gameState): 
	pos(pos), width(width), height(height), texture(texture), game(gameState){}