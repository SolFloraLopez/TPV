#include "Balloon.h"
#include "SDLApplication.h"
#include <cmath>


//Constructor
Balloon::Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, Texture* tex, int colour, PlayState* thisGame, int id) :
	ArrowsGameObject(pos, vel, ancho, alto, tex, thisGame, id)
{
	state = estado;
	color = colour;
}

Balloon::~Balloon() //Destructor
{
}

void Balloon::render() /*const*/ { //Crear un rectangulo destino con las proporciones de los globos y renderiza su textura
	SDL_Rect destRect = SDLGameObject::getDestRect(cols,rows);
	if (inst == 0) SDLGameObject::texture->renderFrame(destRect, color, inst);
	else SDLGameObject::texture->renderFrame(destRect, color, (SDL_GetTicks() - inst) / FRAME_RATE);
};

void Balloon::update()
{
	pos = { pos.getX(), pos.getY() + (vel.getY() * vel.getX()) }; //Actualiza la posicion del globo

	if (pos.getY() < 0 - height / rows) //Devuelve false si el globo se sale de lo alto de la pantalla
	{
		playState->killObject(it);
	}

	if (state) //Si hay colision entre el globo y una flecha y el estado del globo no es false(pinchado)
	{									 // cambia el estado del globo a false y guarda el instante de tiempo en el que ha colisionado
		Arrow* arrow = playState->collision(this, cols, rows);

		if(arrow != nullptr)
		{
			arrow->addHit();
			state = false;
			inst = SDL_GetTicks();
			playState->changeScore(value + pow((arrow->getHits() - 1), 2) * value);
			if(rand() % 3 == 0)playState->rewardspawner(pos, arrow);
		}
	}

	if ((SDL_GetTicks() - inst) / FRAME_RATE == cols)
	{
		playState->killObject(it);
	}
};

void Balloon::loadFromFile(fstream& input)
{
	ArrowsGameObject::loadFromFile(input);
	input >> state;
	input >> color;
}

void Balloon::saveToFile(ofstream& output)
{
	ArrowsGameObject::saveToFile(output);
	output << state << " " << color;
}
