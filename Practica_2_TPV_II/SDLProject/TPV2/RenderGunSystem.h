#pragma once
#include "System.h"

class RenderGunSystem : public System {
public:
	// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego está parado (como en la
	// práctica 1: Press ENTER to start, Game Over, etc.)
	void update() override {};
};