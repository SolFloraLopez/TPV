#include "Bow.h"
#include "SDLApplication.h"


//Constructor
Bow::Bow(Point2D pos, double ancho, double alto, Vector2D vel, Texture* texture, Texture* arrowTex, bool cargado, PlayState* thisGame, int id) :
	ArrowsGameObject(pos, vel, ancho, alto, texture, thisGame, id)
{
	arrowTexture = arrowTex;
	loaded = cargado;
};


//Destructor
//Bow::~Bow() 
//{
//	delete arrow;
//}

void Bow::render() { //Crear un rectangulo destino con las proporciones del arco y renderiza su textura

	//ArrowsGameObject::render();
	texture->render(getDestRect(1, 1));
	if (arrow != nullptr) arrow->render(); //Si flecha no es null llama el render de la misma
};

void Bow::update()
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) }; //Actualiza la posicion del arco

	if (arrow != nullptr)
	{
		arrow->changePos({ pos.getX(), pos.getY() + height / 2 - 15 }); //Si flecha no es null, cambian la posicion de esta
	}
	if (pos.getY() + height > WIN_HEIGHT) pos = { pos.getX(), WIN_HEIGHT - height }; //Mantiene el arco en pantalla

	else if (pos.getY() < 0) pos = { pos.getX(), 0 };
};

void Bow::handleEvent(SDL_Event& event)
{
	double velocity = vel.getY();

	if (event.key.type == SDL_KEYDOWN)
	{

		switch (event.key.keysym.sym) {
		case SDLK_UP: {vel = Vector2D(-1, velocity); break; }

		case SDLK_DOWN: {vel = Vector2D(1, velocity);; break; }

		case SDLK_LEFT: {if (playState->changeAvaliableArrows(0) > 0 && arrow == nullptr) {
			arrow = new Arrow(arrowHeight, arrowWidth, { pos.getX(), pos.getY() + height / 2 - 15 }, { 1, ARROW_VELOCITY }, arrowTexture, playState, 4);
		};
					  break;
		}

		case SDLK_RIGHT: {if (arrow != nullptr) { playState->shoot(arrow); arrow = nullptr; };
					   break;
		}
					   break;
		}
	}

	else vel = Vector2D(0, velocity);// Si no se pulsa ninguna tecla la velocidad del arco es igual a 0
};

void Bow::loadFromFile(fstream& input)
{
	ArrowsGameObject::loadFromFile(input);
}

void Bow::saveToFile(ofstream& output)
{
	ArrowsGameObject::saveToFile(output);
};