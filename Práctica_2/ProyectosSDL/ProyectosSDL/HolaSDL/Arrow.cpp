#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(double height, double width, Point2D pos, Vector2D vel, Texture* tex, Game* game) : 
	ArrowsGameObject(pos, vel, width, height, tex, game) {}; //Constructor

Arrow::~Arrow() //Destructor
{
	//delete texture;
}

//void Arrow::render() const{  //Crear un rectangulo destino con las proporciones de la flecha y renderiza su textura
//	SDL_Rect destRect;
//	destRect.h = height;
//	destRect.w = width;
//	destRect.x = position.getX();
//	destRect.y = position.getY();
//	texture->render(destRect);
//}

void Arrow::update() //Mueve la flecha segun su posicion y velocidad
{
	pos = { pos.getX() + (vel.getY() * vel.getX()), pos.getY()};
	
	if (pos.getX() - width > WIN_WIDTH) game->killObject(it);
}


void Arrow::changePos(Vector2D newPos) //Cambia la posicion de la flecha
{
	pos = { newPos.getX(), newPos.getY() };
}

SDL_Rect* Arrow::returnPointRect() //Devuelve el rectangulo de la punta de la flecha
{
	return new SDL_Rect{ (int)pos.getY(), (int)pos.getX() + ((int)width / 4) * 3 , (int)height / 2, (int)width / 4};
}