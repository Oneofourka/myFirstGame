#include "Board.h"

Board::Board(SDL_Renderer * renderer) {
//	std::cout << "board constructor" << this << std::endl;
	this->renderer = renderer;
	CreateLvl();
}

Board::~Board() {
//	std::cout << "board destructor" << this << std::endl;
}

void Board::Render() {
	for (int i = 0; i < NUMBER_WIDTH; i++) {
		for (int j = 0; j < NUMBER_HEIGHT; j++) {
			if (bricks[i][j]->getState() == true)
				bricks[i][j]->Render();
		}
	}
}

void Board::CreateLvl() {
	for (int i = 0; i < NUMBER_WIDTH; i++) {
		for (int j = 0; j < NUMBER_HEIGHT; j++) {
			bricks[i][j] = new Brick(renderer, i * BRICK_WIDTH, j * BRICK_HEIGHT + DISPLAY_HEIGHT / 5.0);
		}
	}
}

void Board::Clean() {
	for (int i = 0; i < NUMBER_WIDTH; i++) {
		for (int j = 0; j < NUMBER_HEIGHT; j++) {
			delete bricks[i][j];
		}
	}
}

Brick* Board::getBrick(int i, int j) {
	return bricks[i][j];
}

void Board::DestroyBrick(int i, int j) {
	bricks[i][j]->setState(false);
}