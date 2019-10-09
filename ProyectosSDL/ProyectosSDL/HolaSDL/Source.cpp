#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include <string>

using namespace std;

using uint = unsigned int;

void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* textureBackground; // Variable para la textura
	SDL_Texture* textureDog;
	string background = "..\\images\\background1.png";
	string dog = "..\\images\\dog.png";
	SDL_Surface* surfaceBackground = IMG_Load(background.c_str());
	SDL_Surface* surfaceDog = IMG_Load(dog.c_str());

	const uint winWidth = 800;
	const uint winHeight = 600;
	const uint FRAME_RATE = 50;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	textureBackground = SDL_CreateTextureFromSurface(renderer, surfaceBackground);
	SDL_FreeSurface(surfaceBackground);
	textureDog = SDL_CreateTextureFromSurface(renderer, surfaceDog);
	SDL_FreeSurface(surfaceDog);

	int textW, textH; // Para saber el tamaño de la textura
	SDL_QueryTexture(textureDog, nullptr, nullptr, &textW, &textH);
	int textFrameW = textW / 6;
	int textFrameH = textH / 1;
	//Destino
	SDL_Rect destRectDog;
	destRectDog.w = destRectDog.h = 100;
	destRectDog.x = 0;
	destRectDog.y = 400; 
	//Fuente
	SDL_Rect srcRectDog;
	srcRectDog.x = srcRectDog.y = 0;
	srcRectDog.w = textFrameW;
	srcRectDog.h = textFrameH;
	
	   	

	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		int i = 0;
		uint32_t startTime, frameTime;
		startTime = SDL_GetTicks();
		while (!SDL_QuitRequested()) 
		{
			frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= FRAME_RATE) {
				
				destRectDog.x = (0 + 10 * i) % winWidth;

				srcRectDog.x = (textW *i/6) % textW;
				
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				//SDL_RenderClear(renderer); //Borra la pantalla
				SDL_RenderCopy(renderer, textureBackground, nullptr, nullptr); //Fondo
				SDL_RenderCopy(renderer, textureDog, &srcRectDog, &destRectDog); //Perro
				SDL_RenderPresent(renderer); //Muestra la escena

				SDL_Delay(50); // Espera 5 segs. antes de cerrar
				i++;
				startTime = SDL_GetTicks();
			}
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	firstTest();
	return 0;
}