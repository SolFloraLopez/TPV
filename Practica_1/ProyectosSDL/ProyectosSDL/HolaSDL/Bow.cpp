#include "Bow.h"
#include "Game.h"

Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Arrow* arrow, Texture* texture, bool cargado) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), arrow(arrow), texture(texture), cargado(cargado) {};

void Bow::render(std::string filename) const {
	texture->load(filename);	
	SDL_Rect destRect;
	destRect.h = alto;
	destRect.w = ancho;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	texture->render(destRect);
	

};

void Bow::update() {
	if (cargado) {
		Bow::render("..\\");
	}
	else
	{
		Bow::render("..\\");
	}

};

void Bow::handleEvents() {


};