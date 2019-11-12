#include "Bow.h"
#include "Game.h"


//Constructor
Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Texture* texture, Texture* arrowTexture, bool cargado, Game* thisGame) :
	pos(pos), width(ancho), height(alto), vel(vel), texture(texture), arrowTexture(arrowTexture), loaded(cargado), game(thisGame) {};


//Destructor
Bow::~Bow() 
{
	//delete arrow;
	//delete texture;
}

void Bow::render() const { //Crear un rectangulo destino con las proporciones del arco y renderiza su textura
	SDL_Rect destRect;
	destRect.h = height;
	destRect.w = width;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	texture->render(destRect);

	if(arrow != nullptr) arrow->render(); //Si flecha no es null llama el render de la misma
};

void Bow::update() 
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) }; //Actualiza la posicion del arco

	if (arrow != nullptr) arrow->changePos({ pos.getX(), pos.getY() + height / 2 - 15 }); //Si flecha no es null, cambian la posicion de esta

	if (pos.getY() + height > WIN_HEIGHT) pos = { pos.getX(), WIN_HEIGHT - height }; //Mantiene el arco en pantalla

	else if (pos.getY() < 0) pos = { pos.getX(), 0 };
};

void Bow::handleEvent(SDL_Event& event) 
{
	double velocity = vel.getY();

	switch (event.type)
	{
	case SDL_KEYDOWN: //Control del arco con las teclas de flecha
		if (event.key.keysym.sym == SDLK_UP) 
		{
			vel = Vector2D(-1, velocity);
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			vel = Vector2D(1, velocity);
		}

		else if (event.key.keysym.sym == SDLK_LEFT && game->getAvailableArrows() > 0) //Si hay flechas disponibles, crea una nueva
		{
			arrow = new Arrow((double)41, (double)202, { pos.getX(), pos.getY() + height / 2 - 15 }, { 1, ARROW_VELOCITY }, arrowTexture);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && arrow != nullptr) //Si hay una flecha cargada llama al metodo disparar de game y el puntero a arrow se pone en null
		{
			game->shoot(arrow);
			arrow = nullptr;
		}
		break;
	case SDL_KEYUP: // Si no se pulsa ninguna tecla la velocidad del arco es igual a 0
		vel = Vector2D(0, velocity);
		break;
	default:
		break;
	}
};