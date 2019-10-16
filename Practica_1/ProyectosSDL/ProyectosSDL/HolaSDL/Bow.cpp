#include "Bow.h"
#include "Game.h"

Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Arrow* arrow, Texture* texture, bool cargado) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), arrow(arrow), texture(texture), cargado(cargado) {};

Bow::~Bow() 
{
	delete arrow;
	delete texture;
}

void Bow::render() const {
	SDL_Rect destRect;
	destRect.h = alto;
	destRect.w = ancho;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	texture->render(destRect);
};

void Bow::update() 
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) };

	if (pos.getY() + alto > WIN_HEIGHT) pos = { pos.getX(), WIN_HEIGHT - alto };

	else if (pos.getY() < 0) pos = { pos.getX(), 0 };
};

void Bow::handleEvents(SDL_Event& event) 
{
	double velocity = vel.getY();

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)
		{
			vel = Vector2D(-1, velocity);
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			vel = Vector2D(1, velocity);
		}
		break;
	case SDL_KEYUP:
		vel = Vector2D(0, velocity);
		break;
	default:
		break;
	}
};