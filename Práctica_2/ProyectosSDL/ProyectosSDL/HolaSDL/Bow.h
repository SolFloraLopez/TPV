#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include <iostream>

class Game;

class Bow {

private:
	Point2D pos;
	double width;
	double height;
	Vector2D vel;
	Arrow* arrow = nullptr;
	Texture* texture = nullptr;
	Texture* arrowTexture = nullptr;
	Game* game;
	bool loaded;
	
	
public:
	Bow(Point2D pos, double width, double height, Vector2D vel, Texture* texture, Texture* arrowTexture, bool loaded, Game* game);
	~Bow();
	void render() const;
	void update();
	void handleEvents(SDL_Event& event);

};