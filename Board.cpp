#include "Board.h"

Board::Board(SDL_Renderer * renderer) {
//	std::cout << "board constructor" << this << std::endl;
	this->renderer = renderer;
	bricks = nullptr;
	forNextLvl = 0;
	countWidth = NUMBER_WIDTH + forNextLvl;
	countHeight = NUMBER_HEIGHT + forNextLvl;
	for (int i = 0; i < countWidth; i++) 
	{
		bricks[i] = new Brick[countHeight];
	}

	CreateLvl(forNextLvl);
}

Board::~Board() {
//	std::cout << "board destructor" << this << std::endl;
}

void Board::Render() {
	for (int i = 0; i < countWidth; i++) {
		for (int j = 0; j < countHeight; j++) {
			if (bricks[i][j]->getState() == true)
				bricks[i][j]->Render();
		}
	}
}

void Board::CreateLvl(int forNextLvl) {
	checkExistBrick = 0;
	for (int i = 0; i < countWidth; i++) {
		for (int j = 0; j < countHeight; j++) {
			bricks[i][j] = 
			bricks[i][j] = new Brick(renderer, i * BRICK_WIDTH, j * BRICK_HEIGHT + DISPLAY_HEIGHT / 5.0);
		}
	}
}

void Board::Clean() {
	for (int i = 0; i < countWidth; i++) {
		for (int j = 0; j < countHeight; j++) {
			delete bricks[i][j];
		}
	}
}

Brick* Board::getBrick(int i, int j) {
	return bricks[i][j];
}

void Board::DestroyBrick(int i, int j) {
	bricks[i][j]->setState(false);
	checkExistBrick++;
}

int Board::getCheckExistBrick() {
	return checkExistBrick;
}