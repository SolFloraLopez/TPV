#include "Balloon.h"

Balloon::Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, uint inst, Texture* tex) :
	pos(pos), ancho(ancho), alto(alto), vel(vel), estado(estado), inst(inst), texture(tex) {};

void Balloon::render() const {};
void Balloon::update() {};
bool Balloon::move() {};
