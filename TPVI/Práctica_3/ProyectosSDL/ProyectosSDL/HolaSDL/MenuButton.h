#pragma once
#include "SDLGameObject.h"
#include "EventHandler.h"

using CallBackOnClick = void(SDLApplication* game);
const Point2D buttonPos = { 700, 25 };

class MenuButton : public SDLGameObject , public EventHandler
{
private:
	CallBackOnClick* action;
	SDLApplication* game;
public:
	MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* gameState, CallBackOnClick* action, SDLApplication* game);
	virtual void handleEvent(SDL_Event& event);
	virtual void update() {};
	virtual void saveToFile(ofstream& output) {};
	virtual void loadFromFile(fstream& input) {};
};