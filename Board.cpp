#include "Board.h"

Board::Board(SDL_Renderer * renderer, int forNextLvl) {
//	std::cout << "board constructor" << this << std::endl;
	this->renderer = renderer;
	this->forNextLvl = forNextLvl;
	countWidth = NUMBER_WIDTH + forNextLvl;
	countHeight = NUMBER_HEIGHT + forNextLvl;
	bricks = new Brick **[countWidth];
	for (int i = 0; i < countWidth; ++i) 
	{
		bricks[i] = new Brick * [countHeight];
	}
	CreateLvl(forNextLvl);
}

Board::~Board() {
//	std::cout << "board destructor" << this << std::endl;
}

void Board::Render() {
	for (int i = 0; i < countWidth; ++i) {
		for (int j = 0; j < countHeight; ++j) {
			if (bricks[i][j]->getState() == true)
				bricks[i][j]->Render();
		}
	}
}

void Board::CreateLvl(int forNextLvl) {
	checkExistBrick = 0;
	for (int i = 0; i < countWidth; ++i) {
		for (int j = 0; j < countHeight; ++j) {
			bricks[i][j] = new Brick(renderer, i * DISPLAY_WIDTH / (NUMBER_WIDTH + forNextLvl), j * DISPLAY_HEIGHT / (NUMBER_HEIGHT + forNextLvl) / 2 + DISPLAY_HEIGHT / 5.0, DISPLAY_WIDTH / (NUMBER_WIDTH + forNextLvl), DISPLAY_HEIGHT / (NUMBER_HEIGHT + forNextLvl) / 2.0);
		}
	}
}

void Board::Clean() {
	for (int i = 0; i < countWidth; i++)
		for (int j = 0; j < countHeight; j++)
			delete bricks[i][j];

	for (int i = 0; i < countWidth; ++i) 
			delete[] bricks[i];		
	delete bricks;
	
}

Brick * Board::getBrick(int i, int j) {
	return bricks[i][j];
}

void Board::DestroyBrick(int i, int j) {
	bricks[i][j]->setState(false);
	++checkExistBrick;
}

int Board::getCheckExistBrick() {
	return checkExistBrick;
}

int Board::getCountWidth() {
	return countWidth;
}

int Board::getCountHeight() {
	return countHeight;
}

void Board::setCountWidth(int countWidth) {
	this->countWidth = countWidth;
}

void Board::setCountHeight(int countHeight) {
	this->countHeight = countHeight;
}