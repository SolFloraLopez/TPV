#include "ScoreBoard.h"
#include "SDLApplication.h"

ScoreBoard::ScoreBoard(Texture* numTex, Texture* arrTex, PlayState* thisGame) :
	SDLGameObject(scorePos, numberWidth, numberHeight, numbersTex, thisGame)
{
	playState = thisGame;
	numbersTex = numTex;
	arrowTex = arrTex;
	game = thisGame;
}

void ScoreBoard::update()
{
	points = playState->changeScore(0);
	arrowsAmount = playState->changeAvaliableArrows(0);
}

void ScoreBoard::render()
{
	for(int i = 0; i < arrowsAmount; i++)
	{
		arrowTex->render(getDestRect(1, 1, arrowHeight, arrowWidth, { arrowPos.getX() + arrowWidth * i , arrowPos.getY() }));
	}

	int aux = points;
	int i = 0;

	if (aux == 0)
	{
		SDL_Rect destRect = getDestRect(numberCols, 1, numberHeight, numberWidth,
			{ scorePos.getX(), scorePos.getY() });
		numbersTex->renderFrame(destRect, 0, 0);
	}

	else while(aux > 0)
	{
		SDL_Rect destRect = getDestRect(numberCols, 1, numberHeight, numberWidth, 
			{ scorePos.getX() - (double)(numberWidth / numberCols) * i , scorePos.getY()});
		numbersTex->renderFrame(destRect, 0, aux % 10);
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

void ScoreBoard::loadFromFile(fstream& input)
{
}

void ScoreBoard::saveToFile(ofstream& output)
{
}