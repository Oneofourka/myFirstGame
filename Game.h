#pragma once
#include "SDL.h"
#include "MainMenu.h"
#include "Paddle.h"
#include "Ball.h"
#include "Board.h"

const int FPS = 120;
const double frameDelay = 1000.0 / FPS;

enum state {
	MAINMENU,
	GAME,
	PAUSE
};

class Game	{
public:
	Game();
	~Game();

	bool Init();
	void Running();
	void Render();
	void Update();
	void Clean();
	void NewGame();
	void RicochetBoundary(int i);

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	MainMenu * mm;
	state state;
	Paddle * paddle;
	std::vector<Ball*> ball;
};