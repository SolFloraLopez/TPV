#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, /*uint inst,*/ Texture* tex, int color, Game* thisGame) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), estado(estado), /*inst(inst),*/ texture(tex), color(color), game(thisGame) {};

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
	if (inst == 0) texture->renderFrame(destRect, color, inst);
	else texture->renderFrame(destRect, color, (SDL_GetTicks() - inst) / FRAME_RATE);

};

bool Balloon::update() 
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) };

	if (pos.getY() < 0 - alto)
	{
		return false;
	}

	if (game->collision(this) && estado)
	{
		estado = false;
		inst = SDL_GetTicks();
	}

	if ((SDL_GetTicks()- inst) / FRAME_RATE == 6) return false;

	else return true;
};

SDL_Rect* Balloon::returnRect()
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX(), (int)alto / 7, (int)ancho / 6 };
}
