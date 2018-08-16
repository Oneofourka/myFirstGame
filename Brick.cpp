#include "Brick.h"

Brick::Brick(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("images/brick.png");
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->width = BRICK_WIDTH;
	this->height = BRICK_HEIGHT;
	getSomeCoord(width, height);
	state = true;
//	std::cout << "brick constructor" << this << std::endl;
}

Brick::~Brick() {
	SDL_DestroyTexture(brickTexture);
//	std::cout << "brick destructor" << this << std::endl;
}

void Brick::Render() {
	SDL_Rect dstRect;

	dstRect.x = int(x);
	dstRect.y = int(y);
	dstRect.w = int(width);
	dstRect.h = int(height);

	SDL_RenderCopy(renderer, brickTexture, 0, &dstRect);
}

void Brick::setState(bool state) {
	this->state = state;
}

bool Brick::getState() {
	return state;
}