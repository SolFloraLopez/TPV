#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class Arrow : public ArrowsGameObject {
private:
	//double width;
	//double height;
	//Point2D position;
	//Vector2D vel;
	//Texture* texture = nullptr;
	//Game* game;
public:
	Arrow(double alto, double ancho, Point2D pos, Vector2D vel, Texture* tex, Game* game);
	~Arrow();
	//void render() const;
	void changePos(Vector2D pos);
	bool update();
	SDL_Rect* returnPointRect();
};