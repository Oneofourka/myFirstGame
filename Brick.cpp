#include "Brick.h"

Brick::Brick(SDL_Renderer * renderer, double x, double y, double width, double height) : Texture(renderer, x, y, width, height) {
//	std::cout << "brick constructor" << this << std::endl;
	SDL_Surface* surface = IMG_Load("images/brick.png");
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	getSomeCoord(width, height);
	state = true;
}

Brick::~Brick() {
//	std::cout << "brick destructor" << this << std::endl;
	SDL_DestroyTexture(brickTexture);
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