#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>
#include <fstream>

class GameObject {
public:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void saveToFile(ofstream& output) = 0;
	virtual void loadFromFile(fstream& input) = 0;
	virtual ~GameObject() {};
};