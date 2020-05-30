#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(double height, double width, Point2D pos, Vector2D vel,Texture* tex) : //Constructor
	width(width), height(height), position(pos), vel(vel), texture(tex) {};

Arrow::~Arrow() //Destructor
{
	delete texture;
}

void Arrow::render() const{  //Crear un rectangulo destino con las proporciones de la flecha y renderiza su textura
	SDL_Rect destRect;
	destRect.h = height;
	destRect.w = width;
	destRect.x = position.getX();
	destRect.y = position.getY();
	texture->render(destRect);
}

bool Arrow::update() //Mueve la flecha segun su posicion y velocidad
{
	position = { position.getX() + (vel.getY() * vel.getX()), position.getY()};
	
	if (position.getX() - width > WIN_WIDTH) return false;
	else return true;
}


void Arrow::changePos(Vector2D pos) //Cambia la posicion de la flecha
{
	position = { pos.getX(), pos.getY() };
}

SDL_Rect* Arrow::returnPointRect() //Devuelve el rectangulo de la punta de la flecha
{
	return new SDL_Rect{ (int)position.getY(), (int)position.getX() + ((int)width / 4) * 3 , (int)height / 2, (int)width / 4};
}