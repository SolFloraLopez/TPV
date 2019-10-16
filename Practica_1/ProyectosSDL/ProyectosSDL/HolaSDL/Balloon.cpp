#include "Balloon.h"

Balloon::Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, /*uint inst,*/ Texture* tex, int color) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), estado(estado), /*inst(inst),*/ texture(tex), color(color) {};

Balloon::~Balloon()
{
	delete texture;
}

void Balloon::render() const {
	SDL_Rect destRect;
	destRect.h = alto / 7;
	destRect.w = ancho / 6;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	texture->renderFrame(destRect, color, 0);

};

bool Balloon::update() 
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) };

	if (pos.getY() < 0 - alto)
	{
		return false;
	}
	else return true;
};
