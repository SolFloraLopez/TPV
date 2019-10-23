#include "Arrow.h"

Arrow::Arrow(double alto, double ancho, Point2D pos, Vector2D vel,Texture* tex) : 
	ancho(ancho), alto(alto), position(pos), vel(vel), texture(tex) {};

Arrow::~Arrow()
{
	delete texture;
}

void Arrow::render() const{
	SDL_Rect destRect;
	destRect.h = alto;
	destRect.w = ancho;
	destRect.x = position.getX();
	destRect.y = position.getY();
	texture->render(destRect);
}

bool Arrow::update() 
{
	position = { position.getX() + (vel.getY() * vel.getX()), position.getY()};
	return true;
}

void Arrow::rect() {

}

void Arrow::changePos(Vector2D pos)
{
	position = { pos.getX(), pos.getY() + 42 };
}