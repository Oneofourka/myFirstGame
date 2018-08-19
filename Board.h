#pragma once
#include "Brick.h"

class Board{
public:
	Board(SDL_Renderer * renderer, int forNextLvl);
	~Board();
	void Render();
	void CreateLvl(int forNextLvl);
	void Clean();
	Brick * getBrick(int i, int j);
	void DestroyBrick(int i, int j);
	int getCheckExistBrick();
	int getCountWidth();
	int getCountHeight();
	void setCountWidth(int countWidth);
	void setCountHeight(int countHeight);

private:
	SDL_Renderer * renderer;
	int forNextLvl;
	int countWidth, countHeight;
	Brick *** bricks;
	int checkExistBrick;
};