#include "Game.h"

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	state = MAINMENU;
//	std::cout << "game constructor" << this << std::endl;
}

Game::~Game() {
	Clean();
//	std::cout << "game destructor" << this << std::endl;
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
	NewGame();

	Uint32 frameStart;
	int frameTime;

	while (1)
	{
		frameStart = SDL_GetTicks();
//		std::cout << state << std::endl;
		Render();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
			if (state == MAINMENU) {
				for (size_t i = 0; i < mm->Size(); i++)
				{
//					std::cout << state << std::endl;
					if (mm->getButton(i)->Event(&event))
						state = GAME;
				}
			}
		}
		paddle->Move();
		Update();
		for (size_t i = 0; i < ball.size(); i++) {
			RicochetBoundary(i);
			RicochetPaddle(i);
		}
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(Uint32(frameDelay - frameTime));
		}
	}
	SDL_Quit();
}

void Game::Render() {
	SDL_RenderClear(renderer);
	mm->Render();
	paddle->Render();
	for (size_t i = 0; i < ball.size(); i++) {
		ball[i]->Render();
	}
	if (state == GAME)
		board->Render();
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	for (size_t i = 0; i < ball.size(); i++) {
		ball[i]->Update();
	}
	paddle->Update();
}

void Game::Clean() {
	mm->Clean();
	delete mm;
	delete paddle;
	for (size_t i = 0; i < ball.size(); i++)
		delete ball[i];
	board->Clean();
	delete board;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::NewGame() {
	mm = new MainMenu(renderer);
	paddle = new Paddle(renderer, DISPLAY_WIDTH / 2.0 - PADDLE_WIDTH / 2.0, DISPLAY_HEIGHT - PADDLE_HEIGHT);
	ball.push_back(new Ball(renderer, DISPLAY_WIDTH / 2.0 - BALL_WIDTH / 2.0, DISPLAY_HEIGHT - PADDLE_HEIGHT - BALL_HEIGHT));
	board = new Board(renderer);
}

void Game::RicochetBoundary(int i) {
	if (ball[i]->getX() <= 0)			//left boundary
	{
		ball[i]->setX(1);
		ball[i]->setDirX(ball[i]->getDirX() * -1.0);
	//	ball[i]->setContact(0);
	}
	if (ball[i]->getXEnd() >= DISPLAY_WIDTH)		//right boundary
	{
		ball[i]->setX(DISPLAY_WIDTH - ball[i]->getWidth() - 1.0);
		ball[i]->setDirX(ball[i]->getDirX() * -1.0);
	//	ball[i]->setContact(0);
	}
	if (ball[i]->getYEnd() >= DISPLAY_HEIGHT)				//down
	{
		ball[i]->setY(DISPLAY_HEIGHT - ball[i]->getHeight() - 1.0);
		ball[i]->setDirY(ball[i]->getDirY() * -1.0);
		//ball[i]->setContact(0);
	}
	if (ball[i]->getY() <= 400)				//up
	{
		ball[i]->setY(401);
		ball[i]->setDirY(ball[i]->getDirY() * -1.0);
//		ball[i]->setContact(0);
	}
}

void Game::RicochetPaddle(int i) {
	if (ball[i]->getYMiddle() > paddle->getY()) 		//boundary of paddle
	{
		if (ball[i]->getXEnd() > paddle->getX() && ball[i]->getXMiddle() < paddle->getXMiddle()) 
		{
			std::cout << "left boundary of paddle" << std::endl;
			ball[i]->setX(paddle->getX() - ball[i]->getWidth() - 2.0);
			ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		}
		else if (ball[i]->getX() < paddle->getXEnd() && ball[i]->getXMiddle() > paddle->getXMiddle()) 
		{
			std::cout << "right boundary of paddle" << std::endl;
			ball[i]->setX(paddle->getXEnd() + 2.0);
			ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		}
	}
	else if (ball[i]->getYEnd() > paddle->getY())	//up part of paddle
	{					
		if (ball[i]->getXEnd() > paddle->getX() && ball[i]->getX() < paddle->getXEnd()) 	
		{
			double rad = ball[i]->getWidth() / 2.0;		//radius of ball[i]
			if (ball[i]->getXMiddle() == paddle->getXMiddle())
			{	
				std::cout << "middle of paddle" << std::endl;
				ball[i]->setY(paddle->getY() - 2);
				ball[i]->setDirection(0, -1);
			//	ball[i]->setContact(0);
			}
			else if (ball[i]->getXMiddle() < paddle->getX() && paddle->getX() - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow((paddle->getY() - ball[i]->getYMiddle()), 2)))
			{
				std::cout << "left angle" << std::endl;
				ball[i]->setY(paddle->getY() - (paddle->getY() - ball[i]->getYMiddle()) - rad - 2.0);
				ball[i]->setX(paddle->getX() - (paddle->getX() - ball[i]->getXMiddle()) - rad - 2.0);
				ball[i]->setDirection(-2.0 * ((paddle->getWidth() / 2.0 - 1.0) / (paddle->getWidth() / 2.0)), -1);
			//	ball[i]->setContact(0);
			}
			else if (ball[i]->getXMiddle() > paddle->getXEnd() && ball[i]->getXMiddle() - paddle->getXEnd() <= sqrt(pow(rad, 2) - pow(paddle->getY() - ball[i]->getYMiddle(), 2)))
			{	
				std::cout << "right angle" << std::endl;
				ball[i]->setY(paddle->getY() - (paddle->getY() - ball[i]->getYMiddle()) - rad - 2.0);
				ball[i]->setX(paddle->getXEnd() + (ball[i]->getXMiddle() - paddle->getXEnd()) - rad + 2);
				ball[i]->setDirection(2.0 * ((paddle->getWidth() / 2.0 - 1.0) / (paddle->getWidth() / 2.0)), -1);
			//	ball[i]->setContact(0);
			}
			else if (ball[i]->getXMiddle() > paddle->getX() && ball[i]->getXMiddle() < paddle->getXMiddle())
			{	
				std::cout << "left but not angle" << std::endl;
				ball[i]->setY(paddle->getY() - ball[i]->getHeight() - 2);
				ball[i]->setDirection(-2.0 * ((paddle->getXMiddle() - ball[i]->getXMiddle()) / (paddle->getWidth() / 2.0)), -1);
			//	ball[i]->setContact(0);
			}
			else if (ball[i]->getXMiddle() < paddle->getXEnd() && ball[i]->getXMiddle() > paddle->getXMiddle())
			{	
				std::cout << "right but not angle" << std::endl;
				ball[i]->setY(paddle->getY() - ball[i]->getHeight() - 2);
				ball[i]->setDirection(2.0 * ((ball[i]->getXMiddle() - paddle->getXMiddle()) / (paddle->getWidth() / 2.0)), -1);
			//	ball[i]->setContact(0);
			}
		}	
	}
}

void Game::RicochetBrick(int i) {
	for (int t = 0; t < NUMBER_WIDTH; t++)
	{
		for (int k = 0; k < NUMBER_HEIGHT; k++)
		{
			double rad = ball[i]->getWidth() / 2.0;
			if (board->getBrick(t, k)->getState())	//if brick is exist
			{
				if (lBrick <= ball[i]->getXPos() + ball[i]->getWidth() && rBrick >= ball[i]->getXPos() && dBrick >= ball[i]->getYPos() && uBrick <= ball[i]->getYPos() + ball[i]->getHeight())	//check of collision of a ball and a brick
				{	//touching ball and brick
					if (ball[i]->getYPos() <= dBrick && ball[i]->getXMiddle() >= lBrick && ball[i]->getXMiddle() <= rBrick && ball[i]->getYMiddle() > dBrick)
					{		//down
						cout << "down" << endl;
						ball[i]->setYPos(dBrick + 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						if (ball[i]->getContact() != 3)
						{
							board->destroyBrick(t, k);
							ball[i]->setContact(3);
						}
					}
					else if (ball[i]->getXPos() + ball[i]->getWidth() >= lBrick && ball[i]->getYMiddle() >= uBrick && ball[i]->getYMiddle() <= dBrick && ball[i]->getXMiddle() < lBrick)
					{		//letf
						cout << "left" << endl;
						ball[i]->setXPos(lBrick - ball[i]->getWidth() - 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						if (ball[i]->getContact() != 4)
						{
							board->destroyBrick(t, k);
							ball[i]->setContact(4);
						}
					}
					else if (ball[i]->getXPos() <= rBrick && ball[i]->getYMiddle() >= uBrick && ball[i]->getYMiddle() <= dBrick && ball[i]->getXMiddle() > rBrick)
					{	//right
						cout << "right" << endl;
						ball[i]->setXPos(rBrick + 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						if (ball[i]->getContact() != 5)
						{
							board->destroyBrick(t, k);
							ball[i]->setContact(5);
						}
					}
					else if (ball[i]->getYPos() + ball[i]->getHeight() >= uBrick && ball[i]->getXMiddle() >= lBrick && ball[i]->getXMiddle() <= rBrick && ball[i]->getYMiddle() < uBrick)
					{	//up
						cout << "up" << endl;
						ball[i]->setYPos(uBrick - ball[i]->getHeight() - 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						if (ball[i]->getContact() != 6)
						{
							board->destroyBrick(t, k);
							ball[i]->setContact(6);
						}
					}
					else if (ball[i]->getXMiddle() < lBrick && ball[i]->getYMiddle() > dBrick && lBrick - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow(ball[i]->getYMiddle() - dBrick, 2)))
					{	//ld
						board->destroyBrick(t, k);
						cout << "ld" << endl;
						ball[i]->setContact(0);
						if (ball[i]->getDirX() > 0 && ball[i]->getDirY() < 0)
						{
							ball[i]->setXPos(lBrick - (lBrick - ball[i]->getXMiddle()) - ball[i]->getWidth() / 2.0 - 2.0);
							ball[i]->setYPos(dBrick + (ball[i]->getYMiddle() - dBrick) - ball[i]->getHeight() / 2.0 + 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
						else if (ball[i]->getDirX() > 0 && ball[i]->getDirY() > 0)
						{
							ball[i]->setXPos(lBrick - (lBrick - ball[i]->getXMiddle()) - ball[i]->getWidth() / 2.0 - 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						}
						else
						{
							ball[i]->setYPos(dBrick + (ball[i]->getYMiddle() - dBrick) - ball[i]->getHeight() / 2.0 + 2.0);
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
					}
					else if (ball[i]->getXMiddle() > rBrick && ball[i]->getYMiddle() > dBrick && ball[i]->getXMiddle() - rBrick <= sqrt(pow(rad, 2) - pow(ball[i]->getYMiddle() - dBrick, 2)))
					{	//rd
						ball[i]->setContact(0);
						board->destroyBrick(t, k);
						cout << "rd" << endl;
						if (ball[i]->getDirX() < 0 && ball[i]->getDirY() < 0)
						{
							ball[i]->setXPos(rBrick + (ball[i]->getXMiddle() - rBrick) - ball[i]->getWidth() / 2.0 + 2.0);
							ball[i]->setYPos(dBrick + (ball[i]->getYMiddle() - dBrick) - ball[i]->getHeight() / 2.0 + 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
						else if (ball[i]->getDirX() < 0 && ball[i]->getDirY() > 0)
						{
							ball[i]->setXPos(rBrick + (ball[i]->getXMiddle() - rBrick) - ball[i]->getWidth() / 2.0 + 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						}
						else
						{
							ball[i]->setYPos(dBrick + (ball[i]->getYMiddle() - dBrick) - ball[i]->getHeight() / 2.0 + 2.0);
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
					}
					else if (ball[i]->getXMiddle() < lBrick && ball[i]->getYMiddle() < uBrick && lBrick - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow(uBrick - ball[i]->getYMiddle(), 2)))
					{	//lu
						ball[i]->setContact(0);
						board->destroyBrick(t, k);
						cout << "lu" << endl;
						if (ball[i]->getDirX() > 0 && ball[i]->getDirY() > 0)
						{
							ball[i]->setXPos(lBrick - (lBrick - ball[i]->getXMiddle()) - ball[i]->getWidth() / 2.0 - 2.0);
							ball[i]->setYPos(uBrick - (uBrick - ball[i]->getYMiddle()) - ball[i]->getHeight() / 2.0 - 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
						else if (ball[i]->getDirX() > 0 && ball[i]->getDirY() < 0)
						{
							ball[i]->setXPos(lBrick - (lBrick - ball[i]->getXMiddle()) - ball[i]->getWidth() / 2.0 - 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						}
						else
						{
							ball[i]->setYPos(uBrick - (uBrick - ball[i]->getYMiddle()) - ball[i]->getHeight() / 2.0 - 2.0);
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
					}
					else if (ball[i]->getXMiddle() > rBrick && ball[i]->getYMiddle() < uBrick && ball[i]->getXMiddle() - rBrick <= sqrt(pow(rad, 2) - pow(uBrick - ball[i]->getYMiddle(), 2)))
					{	//ru
						ball[i]->setContact(0);
						board->destroyBrick(t, k);
						cout << "ru" << endl;
						if (ball[i]->getDirX() < 0 && ball[i]->getDirY() > 0)
						{
							ball[i]->setXPos(rBrick + (ball[i]->getXMiddle() - rBrick) - ball[i]->getWidth() / 2.0 + 2.0);
							ball[i]->setYPos(uBrick - (uBrick - ball[i]->getYMiddle()) - ball[i]->getHeight() / 2.0 - 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
						else if (ball[i]->getDirX() < 0 && ball[i]->getDirY() < 0)
						{
							ball[i]->setXPos(rBrick + (ball[i]->getXMiddle() - rBrick) - ball[i]->getWidth() / 2.0 + 2.0);
							ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						}
						else
						{
							ball[i]->setYPos(uBrick - (uBrick - ball[i]->getYMiddle()) - ball[i]->getHeight() / 2.0 - 2.0);
							ball[i]->setDirY(-1.0 * ball[i]->getDirY());
						}
					}
				}
			}
		}
	}
}