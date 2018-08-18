#pragma once
#include "SDL.h"
#include "MainMenu.h"
#include "EscMenu.h"
#include "Paddle.h"
#include "Ball.h"
#include "Board.h"
#include "Score_life.h"
#include "HighScore.h"

const int FPS = 120;
const double frameDelay = 1000.0 / FPS;

enum menuState {
	MAINMENU,
	IN_GAME,
	HIGH_SCORE,
	QUIT,
	PAUSE,
	ESC_MENU
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
	void RicochetPaddle(int i);
	void RicochetBrick(int i);
	void CleanGameObject();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	MainMenu * mm;
	EscMenu * em;
	menuState state;
	Paddle * paddle;
	std::vector<Ball*> ball;
	Board * board;
	int life;
	int score;
	Score_Life * scoreRender;
	Score_Life * lifeRender;
	HighScore * highscore;
};