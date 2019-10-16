#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Balloon {

private:
	Point2D pos;
	double ancho;
	double alto;
	int color;
	Vector2D vel;
	bool estado;
	/*uint inst;*/
	Texture* texture = nullptr;
	//Game* game = nullptr;

public:
	Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, /*uint inst,*/ Texture* tex, int color);
	~Balloon();
	void render() const;
	bool update();
};