#pragma once
#include "Brick.h"

class Board{
public:
	Board(SDL_Renderer * renderer);
	~Board();
	void Render();
	void CreateLvl(int forNextLvl);
	void Clean();
	Brick *getBrick(int i, int j);
	void DestroyBrick(int i, int j);
	int getCheckExistBrick();

private:
	SDL_Renderer * renderer;
	int forNextLvl;
	int countWidth, countHeight;
	Brick **bricks = new Brick * [countWidth];
	int checkExistBrick;
};