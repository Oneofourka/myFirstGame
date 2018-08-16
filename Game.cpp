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
	mm = new MainMenu(renderer);
	em = new EscMenu(renderer);

	Uint32 frameStart;
	int frameTime;

	while (state != QUIT)
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
			if (state == MAINMENU) {
				for (size_t i = 0; i < mm->Size(); i++)
				{
					if (mm->getButton(i)->Event(&event))
					{
						if (i == 0)
						{
							NewGame();
							state = PAUSE;
						}
						if (i == 1)
							state = HIGH_SCORE;
						if (i == 2)
							state = QUIT;
					}
				}
			}
			if (state == ESC_MENU) {
				for (size_t i = 0; i < mm->Size(); i++)
				{
					if (em->getButton(i)->Event(&event))
					{
						if (i == 0)
						{
							delete paddle;
							for (size_t i = 0; i < ball.size(); i++)
								delete ball[i];
							board->Clean();
							delete board;
							NewGame();
							state = PAUSE;
						}
						if (i == 1)
						{
							for (size_t i = 0; i < ball.size(); i++)
								delete ball[i];
							board->Clean();

							state = MAINMENU;
						}
						if (i == 2)
							state = QUIT;
					}

				}
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					if (state == IN_GAME)
						state = PAUSE;
					else if (state == PAUSE)
						state = IN_GAME;
				}
				else if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) && state == PAUSE)
					state = IN_GAME;
				else if (event.key.keysym.sym == SDLK_ESCAPE) 
				{
					if (state == IN_GAME || state == PAUSE)
						state = ESC_MENU;
					else if (state == ESC_MENU)
						state = PAUSE;
				}
			}
		}
		if (state == IN_GAME) 
			Update();
		for (size_t i = 0; i < ball.size(); i++) {
			RicochetBoundary(i);
			RicochetPaddle(i);
			RicochetBrick(i);
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
	if (state == MAINMENU)
		mm->Render();
	else if (state == IN_GAME || state == PAUSE)
	{
		paddle->Render();
		for (size_t i = 0; i < ball.size(); i++) {
			ball[i]->Render();
			board->Render();
		}
	}
	else if (state == ESC_MENU)
		em->Render();
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
	em->Clean();
	delete em;
	delete paddle;
	for (size_t i = 0; i < ball.size(); i++)
		delete ball[i];
	board->Clean();
	delete board;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::NewGame() {
	paddle = new Paddle(renderer, DISPLAY_WIDTH / 2.0 - PADDLE_WIDTH / 2.0, DISPLAY_HEIGHT - PADDLE_HEIGHT);
	board = new Board(renderer);
	ball.push_back(new Ball(renderer, paddle->getXMiddle() - BALL_WIDTH / 2.0, paddle->getY() - BALL_HEIGHT));
	life = 3;
}

void Game::RicochetBoundary(int i) {
	if (ball[i]->getX() <= 0)			//left boundary
	{
		ball[i]->setX(1);
		ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		paddle->setState(NOT_ANGLE);
	}
	if (ball[i]->getXEnd() >= DISPLAY_WIDTH)		//right boundary
	{
		ball[i]->setX(DISPLAY_WIDTH - ball[i]->getWidth() - 1.0);
		ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		paddle->setState(NOT_ANGLE);
	}
/*	if (ball[i]->getYEnd() >= DISPLAY_HEIGHT)				//down
	{
		ball[i]->setY(DISPLAY_HEIGHT - ball[i]->getHeight() - 1.0);
		ball[i]->setDirY(ball[i]->getDirY() * -1.0);
		paddle->setState(NOT_ANGLE);
	}*/
	if (ball[i]->getY() <= 0)				//up
	{
		ball[i]->setY(1);
		ball[i]->setDirY(ball[i]->getDirY() * -1.0);
		paddle->setState(NOT_ANGLE);
	}
	if (ball[i]->getYEnd() >= DISPLAY_HEIGHT) 
	{
		life--;
		ball[i]->setY(paddle->getY() - ball[i]->getHeight());
		ball[i]->setX(paddle->getXMiddle() - ball[i]->getWidth() / 2.0);
		ball[i]->setDirection(1, -1);
	}
}

void Game::RicochetPaddle(int i) {
	if (ball[i]->getYMiddle() > paddle->getY()) 		//boundary of paddle
	{
		if (ball[i]->getXEnd() > paddle->getX() && ball[i]->getXMiddle() < paddle->getXMiddle()) 
		{
		//	std::cout << "left boundary of paddle" << std::endl;
			ball[i]->setX(paddle->getX() - ball[i]->getWidth() - 2.0);
			ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		}
		else if (ball[i]->getX() < paddle->getXEnd() && ball[i]->getXMiddle() > paddle->getXMiddle()) 
		{
		//	std::cout << "right boundary of paddle" << std::endl;
			ball[i]->setX(paddle->getXEnd() + 2.0);
			ball[i]->setDirX(ball[i]->getDirX() * -1.0);
		}
	}
	else if (ball[i]->getYEnd() > paddle->getY())	//up part of paddle
	{					
		if (ball[i]->getXEnd() > paddle->getX() && ball[i]->getX() < paddle->getXEnd()) 	
		{
			double rad = ball[i]->getWidth() / 2.0;		//radius of ball[i]
			if (ball[i]->getXMiddle() == paddle->getXMiddle() && paddle->getState() != RIGHT_ANGLE && paddle->getState() != LEFT_ANGLE)
			{	
		//		std::cout << "middle of paddle" << std::endl;
				ball[i]->setY(paddle->getY() - 2);
				ball[i]->setDirection(0, -1);
			}
			else if (ball[i]->getXMiddle() < paddle->getX() && paddle->getX() - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow((paddle->getY() - ball[i]->getYMiddle()), 2)))
			{
		//		std::cout << "left angle" << std::endl;
				ball[i]->setY(paddle->getY() - (paddle->getY() - ball[i]->getYMiddle()) - rad - 2.0);
				ball[i]->setX(paddle->getX() - (paddle->getX() - ball[i]->getXMiddle()) - rad - 2.0);
				ball[i]->setDirection(-2.0 * ((paddle->getWidth() / 2.0 - 1.0) / (paddle->getWidth() / 2.0)), -1);
				paddle->setState(LEFT_ANGLE);
			}
			else if (ball[i]->getXMiddle() > paddle->getXEnd() && ball[i]->getXMiddle() - paddle->getXEnd() <= sqrt(pow(rad, 2) - pow(paddle->getY() - ball[i]->getYMiddle(), 2)))
			{	
		//		std::cout << "right angle" << std::endl;
				ball[i]->setY(paddle->getY() - (paddle->getY() - ball[i]->getYMiddle()) - rad - 2.0);
				ball[i]->setX(paddle->getXEnd() + (ball[i]->getXMiddle() - paddle->getXEnd()) - rad + 2);
				ball[i]->setDirection(2.0 * ((paddle->getWidth() / 2.0 - 1.0) / (paddle->getWidth() / 2.0)), -1);
				paddle->setState(RIGHT_ANGLE);
			}
			else if (ball[i]->getXMiddle() > paddle->getX() && ball[i]->getXMiddle() < paddle->getXMiddle() && paddle->getState() != RIGHT_ANGLE && paddle->getState() != LEFT_ANGLE)
			{	
		//		std::cout << "left but not angle" << std::endl;
				ball[i]->setY(paddle->getY() - ball[i]->getHeight() - 2);
				ball[i]->setDirection(-2.0 * ((paddle->getXMiddle() - ball[i]->getXMiddle()) / (paddle->getWidth() / 2.0)), -1);
			}
			else if (ball[i]->getXMiddle() < paddle->getXEnd() && ball[i]->getXMiddle() > paddle->getXMiddle() && paddle->getState() != RIGHT_ANGLE && paddle->getState() != LEFT_ANGLE)
			{	
		//		std::cout << "right but not angle" << std::endl;
				ball[i]->setY(paddle->getY() - ball[i]->getHeight() - 2);
				ball[i]->setDirection(2.0 * ((ball[i]->getXMiddle() - paddle->getXMiddle()) / (paddle->getWidth() / 2.0)), -1);
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
			double lBrick = board->getBrick(t, k)->getX(); //left wall of brick
			double uBrick = board->getBrick(t, k)->getY(); //up wall of brick
			double rBrick = board->getBrick(t, k)->getXEnd();  //right wall of brick
			double dBrick = board->getBrick(t, k)->getYEnd(); //down wall of brick
			if (board->getBrick(t, k)->getState())		//if exist
			{
				if (ball[i]->getXMiddle() >= lBrick && ball[i]->getXMiddle() <= rBrick && ball[i]->getYMiddle() > dBrick && ball[i]->getY() <= dBrick)
				{
				//	std::cout << "down" << std::endl;
					ball[i]->setY(dBrick + 2.0);
					ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					board->DestroyBrick(t, k);
					paddle->setState(NOT_ANGLE);
				}
				else if (ball[i]->getXMiddle() >= lBrick && ball[i]->getXMiddle() <= rBrick && ball[i]->getYMiddle() < uBrick && ball[i]->getYEnd() >= uBrick)
				{
				//	std::cout << "up" << std::endl;
					ball[i]->setY(uBrick - ball[i]->getHeight() - 2.0);
					ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					board->DestroyBrick(t, k);
					paddle->setState(NOT_ANGLE);
				}
				else if (ball[i]->getYMiddle() >= uBrick && ball[i]->getYMiddle() <= dBrick && ball[i]->getXMiddle() < lBrick && ball[i]->getXEnd() >= lBrick)
				{
				//	std::cout << "left" << std::endl;
					ball[i]->setX(lBrick - ball[i]->getWidth() - 2.0);
					ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					board->DestroyBrick(t, k);
					paddle->setState(NOT_ANGLE);
				}
				else if (ball[i]->getYMiddle() >= uBrick && ball[i]->getYMiddle() <= dBrick && ball[i]->getXMiddle() > rBrick && ball[i]->getX() <= rBrick)
				{
				//	std::cout << "right" << std::endl;
					ball[i]->setX(rBrick + 2.0);
					ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					board->DestroyBrick(t, k);
					paddle->setState(NOT_ANGLE);
				}
				else if (ball[i]->getXMiddle() < lBrick && ball[i]->getYMiddle() < uBrick && lBrick - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow(uBrick - ball[i]->getYMiddle(), 2)))
				{
					board->DestroyBrick(t, k);
				//	std::cout << "lu" << std::endl;
					paddle->setState(NOT_ANGLE);
					if (ball[i]->getDirX() >= 0 && ball[i]->getDirY() >= 0)
					{
						ball[i]->setX(lBrick - (lBrick - ball[i]->getXMiddle()) - rad - 2.0);
						ball[i]->setY(uBrick - (uBrick - ball[i]->getYMiddle()) - rad - 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
					else if (ball[i]->getDirX() > 0 && ball[i]->getDirY() < 0)
					{
						ball[i]->setX(lBrick - (lBrick - ball[i]->getXMiddle()) - rad - 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					}
					else
					{
						ball[i]->setY(uBrick - (uBrick - ball[i]->getYMiddle()) - rad - 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
				}
				else if (ball[i]->getXMiddle() > rBrick && ball[i]->getYMiddle() < uBrick && ball[i]->getXMiddle() - rBrick <= sqrt(pow(rad, 2) - pow(uBrick - ball[i]->getYMiddle(), 2)))
				{
					board->DestroyBrick(t, k);
				//	std::cout << "ru" << std::endl;
					paddle->setState(NOT_ANGLE);
					if (ball[i]->getDirX() < 0 && ball[i]->getDirY() > 0)
					{
						ball[i]->setX(rBrick + (ball[i]->getXMiddle() - rBrick) - rad + 2.0);
						ball[i]->setY(uBrick - (uBrick - ball[i]->getYMiddle()) - rad - 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
					else if (ball[i]->getDirX() < 0 && ball[i]->getDirY() < 0)
					{
						ball[i]->setX(rBrick + (ball[i]->getXMiddle() - rBrick) - rad + 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					}
					else
					{
						ball[i]->setY(uBrick - (uBrick - ball[i]->getYMiddle()) - rad - 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
				}
				else if (ball[i]->getXMiddle() < lBrick && ball[i]->getYMiddle() > dBrick && lBrick - ball[i]->getXMiddle() <= sqrt(pow(rad, 2) - pow(ball[i]->getYMiddle() - dBrick, 2)))
				{
					board->DestroyBrick(t, k);
				//	std::cout << "ld" << std::endl;
					paddle->setState(NOT_ANGLE);
					if (ball[i]->getDirX() > 0 && ball[i]->getDirY() < 0)
					{
						ball[i]->setX(lBrick - (lBrick - ball[i]->getXMiddle()) - rad - 2.0);
						ball[i]->setY(dBrick + (ball[i]->getYMiddle() - dBrick) - rad + 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
					else if (ball[i]->getDirX() > 0 && ball[i]->getDirY() > 0)
					{
						ball[i]->setX(lBrick - (lBrick - ball[i]->getXMiddle()) - rad - 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					}
					else
					{
						ball[i]->setY(dBrick + (ball[i]->getYMiddle() - dBrick) - rad + 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
				}
				if (ball[i]->getXMiddle() > rBrick && ball[i]->getYMiddle() > dBrick && ball[i]->getXMiddle() - rBrick <= sqrt(pow(rad, 2) - pow(ball[i]->getYMiddle() - dBrick, 2)))
				{
					board->DestroyBrick(t, k);
				//	std::cout << "rd" << std::endl;
					paddle->setState(NOT_ANGLE);
					if (ball[i]->getDirX() < 0 && ball[i]->getDirY() < 0)
					{
						ball[i]->setX(rBrick + (ball[i]->getXMiddle() - rBrick) - rad + 2.0);
						ball[i]->setY(dBrick + (ball[i]->getYMiddle() - dBrick) - rad + 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
					else if (ball[i]->getDirX() < 0 && ball[i]->getDirY() > 0)
					{
						ball[i]->setX(rBrick + (ball[i]->getXMiddle() - rBrick) - rad + 2.0);
						ball[i]->setDirX(-1.0 * ball[i]->getDirX());
					}
					else
					{
						ball[i]->setY(dBrick + (ball[i]->getYMiddle() - dBrick) - rad + 2.0);
						ball[i]->setDirY(-1.0 * ball[i]->getDirY());
					}
				}
			}
		}
	}
}