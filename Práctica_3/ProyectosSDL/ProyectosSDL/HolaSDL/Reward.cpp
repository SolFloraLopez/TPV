#include "Game.h"
#include "Reward.h"

Reward::Reward(Point2D pos, Vector2D vel, double width, double height, bool estado, int tipo, Texture* texture, 
	Texture* bubbleTex, Arrow* ArrowPointer, PlayState* game, int id) : ArrowsGameObject(pos, vel, width, height, texture, game, id)
{
	state = estado;
	bubbleTexture = bubbleTex;
	arrow = ArrowPointer;
	type = tipo;
}

Reward::~Reward() {}

void Reward::render()
{
	SDL_Rect destRect = SDLGameObject::getDestRect(cols, rows);

	SDLGameObject::texture->renderFrame(destRect, type, (SDL_GetTicks() / FRAME_RATE) % cols);

	if (state) bubbleTexture->render({ (int)(pos.getX() - bubbleWidth / 6), (int)(pos.getY() - bubbleHeight / 3), bubbleHeight, bubbleWidth });
}

void Reward::update()
{
	pos = { pos.getX(), pos.getY() + vel.getY() };

	if (playState->collision(this, cols, rows) != nullptr && playState->collision(this, cols, rows) != arrow)
	{
		state = false;
	}

	if(pos.getY() > WIN_HEIGHT + height / rows)
	{
		playState->killObject(it);
	}
}

void Reward::handleEvent(SDL_Event& event)
{
	if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point p = { event.button.x, event.button.y };
		if (SDL_PointInRect(&p, &getDestRect(cols, rows)) == SDL_TRUE && !state)
		{
			switch (type)
			{
			case 0: //Control del arco con las teclas de flecha
				playState->changeScore(value);
				break;
			case 1: // Si no se pulsa ninguna tecla la velocidad del arco es igual a 0
				playState->changeAvaliableArrows(1);
				break;
			default:
				break;
			}

			playState->killObject(it);
		}
	}
}

void Reward::loadFromFile(fstream& input)
{
	ArrowsGameObject::loadFromFile(input);
	input >> type;
}

void Reward::saveToFile(ofstream& output)
{
	ArrowsGameObject::saveToFile(output);
	output << type;
}