#include "Butterfly.h"
#include "Game.h"
#include <cmath>

Butterfly::Butterfly(Point2D pos, Vector2D vel, double width, double height, bool estado, Texture* texture, Game* game):
ArrowsGameObject(pos, vel, width, height, texture, game) 
{
	state = estado;
}

Butterfly::~Butterfly(){}

void Butterfly::render() /*const*/ { //Crear un rectangulo destino con las proporciones de los globos y renderiza su textura
	SDL_Rect destRect = ArrowsGameObject::getDestRect(cols,rows);
	
	if (state) {
		texture->renderFrame(destRect,0,(SDL_GetTicks()/FRAME_RATE) % 10);
	}

	else 
	{
		texture->renderFrame(destRect, 0, 1);
	}

};

bool Butterfly::update() {

	if (state)
	{
		if (pos.getX() + width / cols >= WIN_WIDTH || pos.getX() <= 0)
		{
			vel = { -vel.getX(), vel.getY() };
		}

		if (pos.getY() + height / rows >= WIN_HEIGHT || pos.getY() <= 0) vel = { vel.getX(), -vel.getY() };

		pos = { pos.getX() + vel.getX(), pos.getY() + vel.getY() };

		if (game->collision(this, cols, rows))
		{
			state = false;
			vel = { vel.getX(), abs(vel.getY()) };
		}
	}

	else
	{
		pos = { pos.getX(), pos.getY() + vel.getY() };
	}

	return true; //El update NO tiene que ser bool
}