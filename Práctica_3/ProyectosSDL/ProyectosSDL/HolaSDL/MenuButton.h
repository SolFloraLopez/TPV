#pragma once
#include "SDLGameObject.h"
#include "EventHandler.h"

using CallBackOnClick = void(Game* game);

class MenuButton : public SDLGameObject , public EventHandler
{
private:
	CallBackOnClick* action;
public:
	MenuButton(Point2D pos, double width, double height, Texture* texture, Game* gameState);
	virtual void render();
	virtual void handleEvent(SDL_Event& event);
	virtual void update() {};
	virtual void saveToFile(ofstream& output) {};
	virtual void loadFromFile(fstream& input) {};
};