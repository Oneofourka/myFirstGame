#pragma once
#include "Brick.h"

class Board{
public:
	Board(SDL_Renderer * renderer);
	~Board();
	void Render();
	void CreateLvl();
	void Clean();
	Brick *getBrick(int i, int j);
	void DestroyBrick(int i, int j);

private:
	SDL_Renderer * renderer;
	Brick *bricks[NUMBER_WIDTH][NUMBER_HEIGHT];
};