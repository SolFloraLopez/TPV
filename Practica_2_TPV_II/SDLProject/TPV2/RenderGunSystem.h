#pragma once
#include "System.h"

class RenderGunSystem : public System {
public:
	// - dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego est� parado (como en la
	// pr�ctica 1: Press ENTER to start, Game Over, etc.)
	void update() override {};
};