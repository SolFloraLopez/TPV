#include "Balloon.h"
#include "Game.h"


//Constructor
Balloon::Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado,  Texture* tex, int color, Game* thisGame) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), estado(estado), texture(tex), color(color), game(thisGame) {};

Balloon::~Balloon() //Destructor
{
	delete texture;
}

void Balloon::render() const { //Crear un rectangulo destino con las proporciones de los globos y renderiza su textura
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
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) }; //Actualiza la posicion del globo

	if (pos.getY() < 0 - alto) //Devuelve false si el globo se sale de lo alto de la pantalla
	{
		return false;
	}

	if (game->collision(this) && estado) //Si hay colision entre el globo y una flecha y el estado del globo no es false(pinchado)
	{									 // cambia el estado del globo a false y guarda el instante de tiempo en el que ha colisionado
		estado = false;
		inst = SDL_GetTicks();
	}

	if ((SDL_GetTicks()- inst) / FRAME_RATE == 6) return false; 

	else return true;
};

SDL_Rect* Balloon::returnRect() //Devuelve un rectangulo del tamaño de un globo
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX(), (int)alto / 7, (int)ancho / 6 };
}
