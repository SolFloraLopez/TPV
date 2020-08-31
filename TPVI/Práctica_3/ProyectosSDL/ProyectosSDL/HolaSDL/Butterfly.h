#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class GameState;
class Butterfly : public ArrowsGameObject {
private:
	bool state = true;
	const int cols = 10;
	const int rows = 4;
	const int value = -5;
public:
	Butterfly(Point2D pos, Vector2D vel, double width, double height, bool state, Texture* texture, PlayState* game, int ID);
	/*~Butterfly();*/
	virtual void render();
	virtual void update();
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
};