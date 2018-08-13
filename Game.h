#pragma once
#include "SDL.h"
#include "MainMenu.h"
#include "Paddle.h"

const int FPS = 60;
const double frameDelay = 1000.0 / FPS;

class Game	{
public:
	Game();
	~Game();

	bool Init();
	void Running();
	void Render();
	void Update();
	void Clean();
	void newGame();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	MainMenu * mm;
	Uint8 state;
	Paddle * paddle;
};