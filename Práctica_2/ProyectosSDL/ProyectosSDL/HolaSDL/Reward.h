#pragma once
#include "ArrowsGameObject.h"
#include "Arrow.h"
#include "EventHandler.h"
#include <iostream>

class Game;

class Reward : public ArrowsGameObject, public EventHandler
{
private:
	const int cols = 8;
	const int rows = 10;
	const int bubbleHeight = 66;
	const int bubbleWidth = 66;
	const int value = 5;
	int type;

	bool state = true;
	Texture* bubbleTexture;
	Arrow* arrow = nullptr;

public:
	Reward(Point2D pos, Vector2D vel, double width, double height, bool state, int type, Texture* texture, 
		Texture* bubbleTex, Arrow* arrowPointer, Game* game);
	~Reward();
	void render();
	void update();
	SDL_Rect* getCollisionRect(int cols, int rows);
	void handleEvent(SDL_Event& event);
};