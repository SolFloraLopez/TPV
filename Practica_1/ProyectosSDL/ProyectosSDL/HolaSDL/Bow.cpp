#include "Bow.h"
#include "Game.h"

Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Texture* texture, Texture* arrowTexture, bool cargado, Game* thisGame) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), texture(texture), arrowTexture(arrowTexture), cargado(cargado), game(thisGame) {};

Bow::~Bow() 
{
	arrow->~Arrow();
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

	if(arrow != nullptr) arrow->render();
};

void Bow::update() 
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) };

	if (arrow != nullptr) arrow->changePos({ pos.getX(), pos.getY() + alto / 2 - 15 });

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

		else if (event.key.keysym.sym == SDLK_LEFT && game->getAvailableArrows() > 0)
		{
			arrow = new Arrow((double)41, (double)202, { 0,0 }, { 1, ARROW_VELOCITY }, arrowTexture);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && arrow != nullptr)
		{
			game->shoot(arrow);
			arrow = nullptr;
		}
		break;
	case SDL_KEYUP:
		vel = Vector2D(0, velocity);
		break;
	default:
		break;
	}
};