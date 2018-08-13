#pragma once
#include "Brick.h"

class Board : public Texture{
public:
	Board(SDL_Renderer * renderer);
	~Board();
	void CreateLvl();

private:
	Brick bricks[NUMBER_WIDTH][NUMBER_HEIGHT];
};