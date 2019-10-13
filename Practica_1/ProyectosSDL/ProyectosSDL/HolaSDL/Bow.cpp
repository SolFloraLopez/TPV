#include "Bow.h"

Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Arrow* arrow, Texture* texture) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), arrow(arrow), texture(texture) {};

void Bow::render() const {};
void Bow::update() {};
void Bow::handleEvents() {};