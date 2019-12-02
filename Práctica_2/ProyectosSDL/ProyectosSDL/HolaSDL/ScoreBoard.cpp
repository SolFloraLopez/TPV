#include "ScoreBoard.h"
#include "Game.h"

ScoreBoard::ScoreBoard(Texture* numTex, Texture* arrTex, Game* thisGame)
{
	numbersTex = numTex;
	arrowTex = arrTex;
	game = thisGame;
}

void ScoreBoard::update()
{
	points = game->changeScore(0);
	arrowsAmount = game->changeAvaliableArrows(0);
}

void ScoreBoard::render()
{
	for(int i = 0; i < arrowsAmount; i++)
	{
		arrowTex->render(getDestRect(1, 1, arrowHeight, arrowWidth, { arrowPos.getX() + arrowWidth * i , arrowPos.getY() }));
	}

	int aux = points;
	int i = 0;

	while(aux > 0)
	{
		SDL_Rect destRect = getDestRect(numberCols, 1, numberHeight, numberWidth, { WIN_WIDTH / 2 - (double)numberWidth * i , WIN_HEIGHT / 2 });
		numbersTex->renderFrame(destRect, 1, aux % 10);
		aux /= 10;
		i++;
	}
}

SDL_Rect ScoreBoard::getDestRect(int cols, int rows, uint height, uint width, Point2D pos)
{
	SDL_Rect destRect;
	destRect.h = height / rows;
	destRect.w = width / cols;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	return destRect;
}

void ScoreBoard::setItList(list<GameObject*>::iterator iterator)
{
	it = iterator;
}