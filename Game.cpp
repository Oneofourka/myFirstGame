#include "Game.h"

Game::Game() {
	window = NULL;
	renderer = NULL;
	state = 0;	//mainMenu
}

Game::~Game() {
	Clean();
}

bool Game::Init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)		//initialization of all subsystems
	{
		window = SDL_CreateWindow("Arcanoid 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT, false);	//false - fullscreen
		renderer = SDL_CreateRenderer(window, -1, 0);	//-1 for single window, flag = 0;

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //r, g, b, alfa;
		}
		else
		{
			SDL_Log("Unable to render SDL: %s", SDL_GetError());
			success = false;
		}
	}
	else
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		success = false;
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf  Error: %s", TTF_GetError());
		success = false;
	}
	return success;
}

void Game::Running() {
	newGame();

	Uint32 frameStart;
	int frameTime;

	while (1)
	{
		frameStart = SDL_GetTicks();

		Render();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
		paddle->Move();
		Update();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	SDL_Quit();
}

void Game::Render() {
	SDL_RenderClear(renderer);
	mm->Render();
	paddle->Render();
	SDL_RenderPresent(renderer);
}

void Game::Update() {

}

void Game::Clean() {
	mm->Clean();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::newGame() {
	mm = new MainMenu(renderer);
	paddle = new Paddle(renderer, DISPLAY_WIDTH / 2.0 - PADDLE_WIDTH / 2.0, DISPLAY_HEIGHT - PADDLE_HEIGHT);
}
