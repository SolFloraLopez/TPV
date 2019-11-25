#include "Butterfly.h"
#include "Game.h"

Butterfly::Butterfly(Point2D pos, Vector2D vel, double width, double height, bool estado, Texture* texture, Game* game):
ArrowsGameObject(pos, vel, width, height, texture, game) 
{
	state = estado;
}

Butterfly::~Butterfly(){}

void Butterfly::render() /*const*/ { //Crear un rectangulo destino con las proporciones de los globos y renderiza su textura
	SDL_Rect destRect = ArrowsGameObject::getDestRect(cols,rows);
	
	if (state) {
		texture->renderFrame(destRect,1,(SDL_GetTicks()/FRAME_RATE) % 10);
	}
	else {
		texture->renderFrame(destRect, 1, 1);
	}

};

bool Butterfly::update() {

	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) };

	if (state && game->collision(this, cols, rows)) 
	{
		state = false;
	}
	return true; //El update NO tiene que ser bool
}