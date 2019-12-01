#include "Game.h"
#include "Reward.h"

Reward::Reward(Point2D pos, Vector2D vel, double width, double height, bool estado, Texture* texture, 
	Texture* bubbleTex, Arrow* ArrowPointer, Game* game) : ArrowsGameObject(pos, vel, width, height, texture, game)
{
	state = estado;
	bubbleTexture = bubbleTex;
	arrow = ArrowPointer;
}

Reward::~Reward() {}

void Reward::render()
{
	SDL_Rect destRect = ArrowsGameObject::getDestRect(cols, rows);

	texture->renderFrame(destRect, 0, (SDL_GetTicks() / FRAME_RATE) % cols);

	if (state) bubbleTexture->render({ (int)(pos.getX() - bubbleWidth / 6), (int)(pos.getY() - bubbleHeight / 3), bubbleHeight, bubbleWidth });
}

void Reward::update()
{
	pos = { pos.getX(), pos.getY() + vel.getY() };

	if (game->collision(this, cols, rows) != nullptr && game->collision(this, cols, rows) != arrow)
	{
		state = false;
	}
}