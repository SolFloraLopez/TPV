#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"
#include <iostream>

class Game;

class Bow : public ArrowsGameObject, public EventHandler {

private:
	Arrow* arrow = nullptr;
	Texture* arrowTexture = nullptr;
	bool loaded;
	
public:
	Bow(Point2D pos, double width, double height, Vector2D vel, Texture* texture, Texture* arrowTex, bool loaded, Game* game);
	~Bow();
	void render() /*const*/;
	void update();
	void handleEvent(SDL_Event& event);
};