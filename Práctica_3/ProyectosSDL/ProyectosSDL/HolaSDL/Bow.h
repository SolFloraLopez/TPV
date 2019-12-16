#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"
#include <iostream>

class SDLApplication;

class Bow : public ArrowsGameObject, public EventHandler {

private:
	const double arrowHeight = 30;
	const double arrowWidth = 150;

	Arrow* arrow = nullptr;
	Texture* arrowTexture = nullptr;
	bool loaded;
	
public:
	Bow(Point2D pos, double width, double height, Vector2D vel, Texture* texture, Texture* arrowTex, bool loaded, GameState* game, int ID);
	~Bow();
	virtual void render() /*const*/;
	virtual void update();
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
	void handleEvent(SDL_Event& event);
};